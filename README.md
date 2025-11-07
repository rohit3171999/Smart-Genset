# Smart-Genset
Smart Genset Monitoring System using ESP32 that integrates multiple sensors (ADXL345, DS18B20, MQ2, Fuel Level, and SICK WX1941) to monitor vibration, temperature, smoke, fuel level, and RPM in real time for predictive maintenance and remote diagnostics.

# ⚙️ Smart Genset Monitoring System (ESP32-Based)

## 🧩 Overview
The **Smart Genset Monitoring System** is an IoT-based solution designed to monitor critical parameters of a generator set (genset) in real time. It integrates multiple sensors with an **ESP32 microcontroller** to measure:
- Vibration (via ADXL345)
- Temperature (via DS18B20)
- Fuel level (analog sensor)
- RPM (via SICK WX1941 proximity sensor)
- Gas/smoke detection (via MQ2 sensor)

This system provides accurate data that can be used for **predictive maintenance**, **safety alerts**, and **remote monitoring** applications.

---

## 🚀 Features
- ✅ Real-time monitoring of multiple parameters  
- 📈 RPM measurement using pulse counting  
- 🌡️ Temperature monitoring via DS18B20  
- ⛽ Fuel level measurement with analog sensor  
- 💨 Smoke detection using MQ2  
- 🧭 Vibration analysis with ADXL345 accelerometer  
- ⚡ Designed for ESP32 with efficient ADC usage  
- 🔌 Modular and expandable code structure  

---

## 🧠 Components Used
| Component | Function | Connection Pin |
|------------|-----------|----------------|
| **ESP32** | Main controller | — |
| **ADXL345 Accelerometer** | Vibration sensing | I2C (SDA, SCL) |
| **DS18B20 Temperature Sensor** | Temperature measurement | D4 |
| **SICK WX1941** | RPM detection | D34 |
| **Fuel Level Sensor** | Fuel percentage measurement | A32 |
| **MQ2 Gas Sensor** | Smoke/gas detection | A35 |

---

## 🔧 Circuit Overview
- The **ADXL345** communicates via I2C (`SDA`, `SCL` pins of ESP32).  
- The **DS18B20** is connected to digital pin **4** (OneWire protocol).  
- The **SICK WX1941** proximity sensor is connected to **pin 34** with an interrupt for RPM counting.  
- The **Fuel Sensor** and **MQ2 Sensor** use **analog pins 32** and **35** respectively.  

> ⚠️ Ensure that all sensors share a common **GND** and operate at compatible voltage levels (typically 3.3V for ESP32).

---

## 🧾 Code Explanation

### 1. ADXL345 (Vibration)
Measures acceleration in X, Y, and Z axes. Used for detecting abnormal vibrations or mechanical imbalance.

### 2. DS18B20 (Temperature)
Provides precise temperature readings of the generator body or engine surface.

### 3. SICK WX1941 (RPM Sensor)
Counts pulses per revolution using interrupts to calculate RPM every second.

### 4. Fuel Level Sensor
Reads analog voltage to estimate remaining fuel percentage.

### 5. MQ2 (Smoke Sensor)
Monitors exhaust gas or smoke concentration; triggers warning when threshold exceeds.

---

## ⚙️ Installation & Setup

### 1. Required Libraries
Install the following Arduino libraries:
- **Adafruit ADXL345 Unified**
- **Adafruit Unified Sensor**
- **OneWire**
- **DallasTemperature**

You can install them via **Arduino IDE → Tools → Manage Libraries**.

### 2. Hardware Setup
1. Connect sensors as described in the *Circuit Overview* section.  
2. Power the ESP32 via USB or a stable 5V adapter.  
3. Open the Arduino IDE and upload the provided `.ino` file.

### 3. Serial Monitoring
- Open the **Serial Monitor** at **115200 baud rate**.  
- You’ll see real-time readings:
  - Vibration data (X, Y, Z)
  - Temperature in °C
  - RPM count
  - Fuel percentage
  - Smoke alert status  

---


