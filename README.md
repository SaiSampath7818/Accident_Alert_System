# 🚨 ESP32-Based Accident Alert System

This is a real-time accident detection and alert system built using the ESP32 microcontroller. It uses an **ADXL335 accelerometer** to detect sudden acceleration (crashes) and a **NEO-6M GPS module** to determine the exact location of the incident. Upon detecting a potential accident, the system automatically sends location and status information via **Bluetooth** to a paired mobile device or computer.

## 📦 Features

- 📍 Real-time accident detection using acceleration threshold
- 🛰️ GPS-based location tracking
- 🔗 Bluetooth message transmission (ESP32 classic Bluetooth)
- ⏱️ Smart flag-resetting system to avoid repeated alerts
- 🧠 Embedded roll, pitch, and yaw calculations (extendable for future use)

## 🛠️ Hardware Components

| Component         | Description                    |
|-------------------|---------------------------------|
| ESP32             | Microcontroller with Bluetooth  |
| ADXL335           | 3-axis analog accelerometer     |
| NEO-6M GPS        | GPS module with UART interface  |
| Power Supply      | USB or Battery (5V recommended) |


> ⚠️ **Note**: The NEO-6M GPS module **must be placed in an open space** (preferably outdoors) with a clear view of the sky for accurate satellite lock. Indoors or enclosed areas can result in weak or no GPS signal.

---

### ADXL335 → ESP32 Pin Mapping

- X-out → GPIO36 (VP / A0)
- Y-out → GPIO39 (VN / A3)
- Z-out → GPIO34 (A6)

### NEO-6M GPS → ESP32 Pin Mapping

- GPS TX → GPIO16 (ESP32 RX2)
- GPS RX → GPIO17 (ESP32 TX2)

## 🔌 Software Requirements

- Arduino IDE
- ESP32 Board Package Installed
- Libraries:
  - `TinyGPSPlus` by Mikal Hart
  - Built-in `BluetoothSerial`

## ⚙️ How It Works

1. The ESP32 continuously reads accelerometer and GPS data.
2. If the **net acceleration exceeds 8.5g**, it is considered a crash.
3. The system then:
   - Sends an alert message via Bluetooth
   - Includes GPS latitude and longitude
   - Prevents repeated alerts for 10 seconds (debouncing)
4. After 10 seconds, it resets and resumes monitoring.

## ▶️ Getting Started

1. Connect the hardware as per the schematic.
2. Install the required libraries in Arduino IDE.
3. Upload the code to your ESP32 board.
4. Pair your mobile/computer to the ESP32 via Bluetooth (named `ESP32-AccidentAlert`).
5. Monitor the output using any serial Bluetooth app or terminal.

## 📈 Example Output

```
Net Acceleration (g): 9.21
🚨 Accident Detected!
Location: Lat=12.971598, Lng=77.594566
