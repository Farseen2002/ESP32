#include <WiFi.h>

const char* ssid = "FRSN 1768";
const char* password = "11111111";

#define LED_PIN 5   // change to 2 if you want builtin LED on many dev boards

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
    // optional timeout to avoid infinite loop:
    if (millis() - start > 20000) {
      Serial.println("\nFailed to connect within 20s. Restarting.");
      // you could attempt to restart or handle gracefully
      // ESP.restart();
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi not connected. You can still try connecting clients on AP or check settings.");
  }

  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // get new client
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    unsigned long lastActivity = millis();

    while (client.connected() && (millis() - lastActivity < 5000)) { // timeout 5s
      if (client.available()) {
        char c = client.read();
        lastActivity = millis();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // send HTTP response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<!doctype html><html><head><meta charset='utf-8'><title>ESP32 LED</title></head><body>");
            client.print("Click <a href=\"/H\">here</a> to turn the LED on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED off.<br>");
            client.print("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
          // check for request paths
          if (currentLine.endsWith("GET /H")) {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("LED ON");
          } else if (currentLine.endsWith("GET /L")) {
            digitalWrite(LED_PIN, LOW);
            Serial.println("LED OFF");
          }
        }
      }
    }
    // give the client time to receive the data
    delay(1);
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
