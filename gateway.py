import serial
import firebase_admin
from firebase_admin import credentials, db
import joblib

# Load ML model
model = joblib.load("model.pkl")

# Firebase setup
cred = credentials.Certificate("serviceAccountKey.json")

firebase_admin.initialize_app(cred, {
    "databaseURL": "https://watermonitoring-36dcf-default-rtdb.asia-southeast1.firebasedatabase.app"
})

# Serial setup
ser = serial.Serial("COM8", 115200, timeout=1)

print("Gateway started... Waiting for receiver data")


def reuse_logic(ph, turbidity, tds):
    if 6.5 <= ph <= 8.5 and turbidity < 5 and tds <= 500:
        return "Drinking"
    elif 6.0 <= ph <= 9.0 and turbidity < 10 and tds <= 1000:
        return "Irrigation"
    elif tds < 1500:
        return "Industrial"
    else:
        return "Not Reusable"
def purpose_analysis(ph, turbidity, tds):
    
    if 6.5 <= ph <= 8.5 and turbidity < 5 and tds <= 500:
        return "Safe for Drinking"

    elif 6.0 <= ph <= 9.0 and turbidity < 10 and tds <= 1000:
        return "Not suitable for drinking, but safe for Irrigation"

    elif tds < 1500:
        return "Unsafe for drinking & irrigation, usable for Industrial purposes"

    else:
        return "Highly Unsafe water – Not suitable for any use"
def ml_suggestion(status, ph, turbidity, temperature, tds, methane, ammonia):  
    suggestions = []

    if status == "Safe":
        suggestions.append("Water quality acceptable. Continue monitoring")

    elif status == "Moderate":
        suggestions.append("Moderate quality. Treatment recommended before use")

    elif status == "Unsafe":
        suggestions.append("Unsafe water. Immediate corrective treatment required")
    if ph < 6.5:
        suggestions.append("Increase pH using alkaline treatment")
    elif ph > 8.5:
        suggestions.append("Reduce pH using neutralization treatment")

    if turbidity > 10:
        suggestions.append("Use filtration or sedimentation to reduce turbidity")

    if tds > 500:
        suggestions.append("Use RO or ion-exchange treatment to reduce TDS")

    if temperature > 32:
        suggestions.append("Temperature is high; monitor thermal pollution or fish stress")

    if methane > 50:
        suggestions.append("High methane detected; check organic waste decomposition")

    if ammonia > 25:
        suggestions.append("High ammonia detected; improve aeration and reduce waste load")

    if len(suggestions) == 0:
        return "Water condition is acceptable. Continue regular monitoring."

    return " | ".join(suggestions)
while True:
    try:
        line = ser.readline().decode("utf-8", errors="ignore").strip()

        if not line:
            continue

        print("Received:", line)

        if not line.startswith("DATA:"):
            continue

        clean = line.replace("DATA:", "")
        parts = clean.split(",")

        if len(parts) != 11:
            print("Invalid data format")
            print("Expected: DATA:location,ph,turbidity,temperature,tds,conductivity,methane,ammonia,distance,latitude,longitude")
            continue

        location = parts[0]

        ph = float(parts[1])
        turbidity = float(parts[2])
        temperature = float(parts[3])
        tds = float(parts[4])
        conductivity = float(parts[5])
        methane = float(parts[6])
        ammonia = float(parts[7])
        distance = float(parts[8])
        latitude = float(parts[9])
        longitude = float(parts[10])

        # ML prediction
        # ML prediction
        X = [[ph, turbidity, temperature, tds, conductivity]]  
        status = model.predict(X)[0]

        # ML recommendation
        suggestion = ml_suggestion(
    status,
    ph,
    turbidity,
    temperature,
    tds,
    methane,
    ammonia
        )

        # Reuse suggestion
        reuse = reuse_logic(ph, turbidity, tds)

        ref = db.reference(location)
        purpose = purpose_analysis(ph, turbidity, tds)

        ref.set({
            "ph": ph,
            "turbidity": turbidity,
            "temperature": temperature,
            "tds": tds,
            "conductivity": conductivity,
            "methane": methane,
            "ammonia": ammonia,
            "distance": distance,
            "latitude": latitude,
            "longitude": longitude,
            "mlStatus": status,
            "mlSuggestion": suggestion,
            "reuseSuggestion": reuse,
            "purpose": purpose
        })
        purpose = purpose_analysis(ph, turbidity, tds)

        print("Uploaded to Firebase under", location)
        print("ML Status:", status)
        print("Reuse Suggestion:", reuse)

    except Exception as e:
        print("Error:", e)