#define BLYNK_TEMPLATE_ID "TMPL3TBnSPxaV"
#define BLYNK_TEMPLATE_NAME "Visual Display"
#define BLYNK_AUTH_TOKEN "4Kzfl6iKq6lYIxDOD5jPVPTSkImTnU9c"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "DHTesp.h"

// ---------- CONFIG ----------
char ssid[] = "FRSN 1768";
char pass[] = "11111111";

const int DHT_PIN = 4;          // DATA pin connected to GPIO4
// Change to DHT11 if you're using DHT11. DHTesp uses DHTesp::DHT11 or DHTesp::DHT22
const int DHT_TYPE = DHTesp::DHT11;  

DHTesp dht;

BlynkTimer timer;

// Send sensor readings to Blynk every N seconds
const unsigned long SEND_INTERVAL_MS = 5000; // 5 seconds

void sendSensorReadings() {
  // Read temperature & humidity from DHT
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature(); // Celsius. Use getTemperature(true) for Fahrenheit

  // Check for NaN (failed read)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print to Serial for debugging
  Serial.print("Temp: ");
  Serial.print(temperature, 2);
  Serial.print(" °C, Hum: ");
  Serial.print(humidity, 2);
  Serial.println(" %");

  // Send to Blynk (V1 = Temp, V2 = Humidity)
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("DHT + Blynk Example");

  // Initialize DHT
  dht.setup(DHT_PIN, DHTesp::DHT11); // set type here (DHT22). change if DHT11

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Start periodic sensor reads
  timer.setInterval(SEND_INTERVAL_MS, sendSensorReadings);
}

void loop() {
  Blynk.run();
  timer.run();
}
