#define BLYNK_PRINT Serial

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3RXjLYPY_"
#define BLYNK_TEMPLATE_NAME "LED"
#define BLYNK_AUTH_TOKEN    "rVh2ntsHeRweXo1eCP-8gFbGN6Lv6VnQ"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FRSN 1768";
char pass[] = "11111111";

// Define the Pin connected to the Relay
// If using a different pin, change it here
#define RELAY_PIN 23

// This function is called every time the Virtual Pin V0 state changes
// in the Blynk App
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int pinValue = param.asInt(); 

  // Control the relay based on the value
  // Note: Many relays are "Active LOW" (0 turns ON, 1 turns OFF)
  // If your relay works opposite, swap HIGH and LOW below.
  if (pinValue == 1) {
    digitalWrite(RELAY_PIN, HIGH); // Turn Relay ON
    Serial.println("Light turned ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Turn Relay OFF
    Serial.println("Light turned OFF");
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set Relay Pin as Output
  pinMode(RELAY_PIN, OUTPUT);
  
  // Initialize Relay to OFF (Optional, prevents flicker on boot)
  digitalWrite(RELAY_PIN, LOW);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  // Run Blynk services
  Blynk.run();
}