// ============================
// AquaSentinel Receiver
// ESP32 + LoRa Receiver
// ============================

#include <SPI.h>
#include <LoRa.h>

// -------- LoRa Pins --------
#define LORA_SS   5
#define LORA_RST  14
#define LORA_DIO0 26

String locationName = "Lake1";

void setup() {

  Serial.begin(115200);

  Serial.println("LoRa Receiver Starting...");

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Init Failed!");
    while (1);
  }

  LoRa.setSyncWord(0x12);

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa Receiver Ready");
}

void loop() {

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    String receivedData = "";

    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }

    Serial.println("\n📩 RECEIVED DATA:");
    Serial.println(receivedData);

    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());

    // -------- Parse Values --------
    float temperature = getValue(receivedData, "T:");
    float ph          = getValue(receivedData, "P:");
    float tds         = getValue(receivedData, "S:");
    float turbidity   = getValue(receivedData, "N:");
    float distance    = getValue(receivedData, "D:");
    float methane     = getValue(receivedData, "M:");
    float ammonia     = getValue(receivedData, "A:");
    float latitude    = getValue(receivedData, "LAT:");
    float longitude   = getValue(receivedData, "LNG:");

    // -------- Mobility Detection --------
    String stuckStatus = "Unstuck";

    if (distance <= 5) {
      stuckStatus = "Stuck";
      Serial.println("⚠️ ALERT: System may be STUCK!");
    }
    else {
      Serial.println("✅ System moving normally");
    }

    // -------- Display --------
    Serial.println("\n===== AquaSentinel Report =====");

    Serial.print("Temperature: ");
    Serial.println(temperature);

    Serial.print("pH: ");
    Serial.println(ph);

    Serial.print("TDS: ");
    Serial.println(tds);

    Serial.print("Turbidity: ");
    Serial.println(turbidity);

    Serial.print("Distance: ");
    Serial.println(distance);

    Serial.print("Methane: ");
    Serial.println(methane);

    Serial.print("Ammonia: ");
    Serial.println(ammonia);

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);

    Serial.print("Longitude: ");
    Serial.println(longitude, 6);

    Serial.print("Mobility: ");
    Serial.println(stuckStatus);

    Serial.println("================================");

    // -------- Send DATA for gateway.py --------
    Serial.print("DATA:");

    Serial.print(locationName);
    Serial.print(",");

    Serial.print(ph);
    Serial.print(",");

    Serial.print(turbidity);
    Serial.print(",");

    Serial.print(temperature);
    Serial.print(",");

    Serial.print(tds);
    Serial.print(",");

    Serial.print(0);
    Serial.print(",");

    Serial.print(methane);
    Serial.print(",");

    Serial.print(ammonia);
    Serial.print(",");

    Serial.print(distance);
    Serial.print(",");

    Serial.print(latitude, 6);
    Serial.print(",");

    Serial.println(longitude, 6);
  }
}

// -------- Function --------
float getValue(String data, String key) {

  int start = data.indexOf(key);

  if (start == -1)
    return 0;

  start = start + key.length();

  int end = data.indexOf("|", start);

  if (end == -1)
    end = data.length();

  return data.substring(start, end).toFloat();
}