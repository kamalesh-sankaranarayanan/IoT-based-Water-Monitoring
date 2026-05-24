# AquaSentinel 🌊

AquaSentinel is an IoT-based Smart Water Quality Monitoring System developed using ESP32, LoRa, Firebase, and Machine Learning. The system monitors real-time water parameters and displays them on a responsive web dashboard.

## 🚀 Features

- Real-time water quality monitoring
- LoRa-based long-range wireless communication
- Firebase Realtime Database integration
- Responsive web dashboard (mobile + desktop)
- Machine Learning-based water quality analysis
- Water reuse recommendations
- Live alerts and notifications
- GPS tracking support
- Mobility status detection (Stuck / Unstuck)
- Sensor trend visualization using Chart.js
- PDF/DOC report generation support

---

## 📊 Parameters Monitored

- pH
- Turbidity
- Temperature
- TDS
- Conductivity
- Methane Gas
- Ammonia Gas
- Distance
- GPS Location
- Mobility Status

---

## 🛠 Technologies Used

### Hardware
- ESP32
- LoRa SX1278 Module
- pH Sensor
- Turbidity Sensor
- TDS Sensor
- Ultrasonic Sensor
- Gas Sensors

### Software
- Arduino IDE
- Python
- Firebase
- HTML
- CSS
- JavaScript
- Chart.js
- Machine Learning (Scikit-learn)

---

## 🔄 System Architecture

Sensors → ESP32 Transmitter → LoRa → ESP32 Receiver → Python Gateway → Firebase → Web Dashboard

---

## 📁 Project Structure

```text
AquaSentinel/
│
├── arduino/
│   └── transmitter.ino
│   └── receiver.ino
│
├── gateway.py
├── model.pkl
├── lora.py
└── serviceAccountKey.json
│
├── frontend/
│   ├── index.html
│   ├── sensor.html
│   ├── style.css
│   └── images/
│
├── firebase.json
├── requirements.txt
└── README.md