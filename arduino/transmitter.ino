// ============================
// AquaSentinel Transmitter
// ESP32 + Sensors + LoRa
// ============================

#include <SPI.h>
#include <LoRa.h>

// -------- LoRa Pins --------
#define LORA_SS   5
#define LORA_RST  14
#define LORA_DIO0 26

// -------- Sensor Pins --------
#define PH_PIN      34
#define TDS_PIN     35
#define TURB_PIN    32
#define TEMP_PIN    33
#define TRIG_PIN    13
#define ECHO_PIN    12

// -------- Calibration --------
const int AIR_VAL = 1600;
const int WATER_VAL = 2100;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Init Failed!");
    while (1);
  }

  LoRa.setSyncWord(0x12);

  Serial.println("AquaSentinel Transmitter Ready");
}

void loop() {

  // -------- Temperature --------
  int tempRaw = analogRead(TEMP_PIN);
  float temperature = map(tempRaw, 0, 4095, 20, 40);

  // -------- pH --------
  int phRaw = analogRead(PH_PIN);
  float ph = map(phRaw, 0, 4095, 0, 14);

  // -------- TDS --------
  int tdsRaw = analogRead(TDS_PIN);
  float tds = map(tdsRaw, 0, 4095, 0, 1000);

  // -------- Turbidity --------
  int turbRaw = analogRead(TURB_PIN);

  float turbidity = mapFloat(
    turbRaw,
    AIR_VAL,
    WATER_VAL,
    0,
    500
  );

  turbidity = constrain(turbidity, 0, 500);

  // -------- Distance --------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  // -------- Gas Sensors --------
  float methane = 0.0;
  float ammonia = 0.0;

  // -------- GPS --------
  float latitude = 0.000000;
  float longitude = 0.000000;

  // -------- Create Packet --------
  String data = "";

  data += "T:" + String(temperature, 1);
  data += "|P:" + String(ph, 1);
  data += "|S:" + String(tds, 1);
  data += "|N:" + String(turbidity, 1);
  data += "|D:" + String(distance, 1);
  data += "|M:" + String(methane, 1);
  data += "|A:" + String(ammonia, 1);
  data += "|LAT:" + String(latitude, 6);
  data += "|LNG:" + String(longitude, 6);

  // -------- Send LoRa --------
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();

  // -------- Serial Monitor --------
  Serial.println("\n===== TRANSMITTING =====");
  Serial.println(data);
  Serial.println("========================");

  delay(3000);
}

// -------- Float Map Function --------
float mapFloat(
  float x,
  float in_min,
  float in_max,
  float out_min,
  float out_max
) {

  return (x - in_min) *
         (out_max - out_min) /
         (in_max - in_min) +
         out_min;
}