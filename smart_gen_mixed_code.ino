#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ==== ADXL345 Accelerometer ====
Adafruit_ADXL345_Unified adxl = Adafruit_ADXL345_Unified(12345);
// ==== Fuel Level Sensor ====
#define FUEL_SENSOR_PIN 32  // Analog pin where the fuel level sensor is connected
#define VREF 5.0            // Voltage reference of ESP32 (typically 5V)


// ==== DS18B20 Temperature Sensor ====
const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// ==== SICK WX1941 Proximity Sensor ====
#define RPM_SENSOR_PIN 34
volatile int pulseCount = 0;
unsigned long lastRPMTime = 0;
float rpm = 0;

// ==== MQ2 Gas Sensor ====
#define MQ2_PIN 35
int mq2Value = 0;
float mq2Voltage = 0.0;

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);

  // --- ADXL345 Setup ---
  if (!adxl.begin()) {
    Serial.println("ADXL345 not detected. Check connections!");
    while (1);
  }
  adxl.setRange(ADXL345_RANGE_16_G);
  Serial.println("ADXL345 Initialized.");

  // --- DS18B20 Setup ---
  sensors.begin();
  Serial.println("DS18B20 Initialized.");

  // --- SICK WX1941 Proximity Sensor Setup ---
  pinMode(RPM_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RPM_SENSOR_PIN), countPulse, FALLING);

  // --- MQ2 Setup ---
  analogSetAttenuation(ADC_11db);  // For full 0–3.3V range on ESP32
  Serial.println("MQ2 sensor initialized.");
}

void loop() {
  // === ADXL345: Vibration Data ===
  sensors_event_t event;
  adxl.getEvent(&event);
  Serial.print("[ADXL345] X: "); Serial.print(event.acceleration.x); Serial.print(" m/s² ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" m/s² ");
  Serial.print("Z: "); Serial.println(event.acceleration.z); Serial.print(" m/s² ");

  // === DS18B20: Temperature ===
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print("[DS18B20] Temperature: "); Serial.print(temperatureC); Serial.println(" °C");

  // === SICK WX1941: RPM ===
  unsigned long currentTime = millis();
  if (currentTime - lastRPMTime >= 1000) {
    rpm = pulseCount * 60;  // 1 pulse = 1 revolution
    Serial.print("[SICK WX1941] RPM: "); Serial.println(rpm);
    pulseCount = 0;
    lastRPMTime = currentTime;
  }
  // === Fuel Level Sensor ===
  int rawValue = analogRead(FUEL_SENSOR_PIN);             // Read raw ADC value (0–1023)
  float voltage = rawValue * (VREF / 1023.0);              // Convert to voltage

  // Example mapping (adjust according to your sensor)
  // Assuming 0V = empty tank, 5V = full tank (adjust if your range is different)
  float fuelPercentage = map(rawValue, 4095, 1830, 0, 100);  // Calibrated range

  // Clamp values
  fuelPercentage = constrain(fuelPercentage, 0, 100);

  // Print to Serial Monitor
  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Fuel Level: ");
  Serial.print(fuelPercentage);
  Serial.println(" %");

  // === MQ2: Smoke Detection ===
  mq2Value = analogRead(MQ2_PIN);
  mq2Voltage = mq2Value * (3.3 / 4095.0);
  Serial.print("[MQ2] ADC: "); Serial.print(mq2Value);
  Serial.print(" | Voltage: "); Serial.print(mq2Voltage, 2);
  if (mq2Value > 2000) {
    Serial.println(" ⚠️  Smoke Detected!");
  } else {
    Serial.println(" - Normal");
  }

  Serial.println("--------------------------------------------------");
  delay(1000);  // Sampling interval
}
