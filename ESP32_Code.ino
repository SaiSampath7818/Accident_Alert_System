#include <TinyGPSPlus.h>
#include <math.h>
#include "BluetoothSerial.h"

// ========== PIN DEFINITIONS ==========
#define RXD2 16  // GPS TX → ESP32 RXD2
#define TXD2 17  // (optional)
const int x_out = A0; // ADXL335 X
const int y_out = A3; // ADXL335 Y
const int z_out = A6; // ADXL335 Z

// ========== GLOBAL OBJECTS ==========
TinyGPSPlus gps;
BluetoothSerial serialBT;

bool accidentSent = false;
unsigned long lastResetTime = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // GPS on Serial2
  serialBT.begin("ESP32-AccidentAlert"); // Bluetooth
  Serial.println("System Initialized...");
}

// ========== DISPLAY LOCATION ==========
void sendLocationToBT() {
  if (gps.location.isValid()) {
    String lat = String(gps.location.lat(), 6);
    String lng = String(gps.location.lng(), 6);
    String gpsData = "Location: Lat=" + lat + ", Lng=" + lng;
    serialBT.println(gpsData);
    Serial.println(gpsData);
  } else {
    serialBT.println("Location: INVALID");
    Serial.println("Location: INVALID");
  }
}

void loop() {
  // --------- Read GPS Data ---------
  while (Serial2.available()) {
    gps.encode(Serial2.read());
  }

  // --------- Read Accelerometer ---------
  int x_adc = analogRead(x_out);
  int y_adc = analogRead(y_out);
  int z_adc = analogRead(z_out);

  double x_g = (((double)x_adc * 3.3 / 4096) - 1.65) / 0.330;
  double y_g = (((double)y_adc * 3.3 / 4096) - 1.65) / 0.330;
  double z_g = (((double)z_adc * 3.3 / 4096) - 1.80) / 0.330;

  double net_acc = sqrt(x_g * x_g + y_g * y_g + z_g * z_g);

  // --------- Accident Detection ---------
  if (net_acc >= 8.5 && !accidentSent) {
  Serial.println("🚨 Accident Detected!");
  serialBT.println("🚨 ACCIDENT DETECTED");

  String accData = "Net Acceleration: " + String(net_acc, 2) + " g";
  Serial.println(accData);
  serialBT.println(accData);

  sendLocationToBT();  // Send GPS coordinates

  accidentSent = true;
  lastResetTime = millis();
}


  // --------- Reset Flag After 10s ---------
  if (accidentSent && (millis() - lastResetTime > 10000)) {
    accidentSent = false;
  }

  delay(1000);
}


/*
ADXL335---ESP32

x-out---VP
y-out---VN
z-out---34


gps---esp32
rx---16
tx---17
*/