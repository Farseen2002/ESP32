#define BLYNK_TEMPLATE_ID "TMPL3RXjLYPY_"
#define BLYNK_TEMPLATE_NAME "LED"
#define BLYNK_AUTH_TOKEN "rVh2ntsHeRweXo1eCP-8gFbGN6Lv6VnQ"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "FRSN 1768";
char pass[] = "11111111";

// Most dev boards have the onboard LED on GPIO 5. If yours is different, change LED_PIN.
const int LED_PIN = 5;

// If your onboard LED is active-low (common), set this to true to invert output.
const bool INVERT_LED = false;
// ----------------------------

BLYNK_WRITE(V0) {
  int v = param.asInt(); // 1 = ON, 0 = OFF
  // If LED is active-low, invert the logic:
  if (INVERT_LED) digitalWrite(LED_PIN, v ? LOW : HIGH);
  else digitalWrite(LED_PIN, v ? HIGH : LOW);

  Serial.print("V0=");
  Serial.println(v);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  if (INVERT_LED) digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


void loop() {
  Blynk.run();
}
