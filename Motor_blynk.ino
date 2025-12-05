#define BLYNK_TEMPLATE_ID "TMPL3LmrL-qj-"
#define BLYNK_TEMPLATE_NAME "Joystick "
#define BLYNK_AUTH_TOKEN "dN3wFLPmYn9m71ziTGYg1MowXXBEN5Q9"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk credentials
char ssid[] = "FRSN 1768";
char pass[] = "11111111";

// Motor driver pins
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12

int joystickX = 0; // Renamed for clarity: will store X-axis value from V1
int joystickY = 0; // Renamed for clarity: will store Y-axis value from V0

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ensure motors are stopped at startup
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Function to control car movement
void moveCar()
{
  // --- Forward/Backward Control (using joystickY from V0) ---
  if (joystickY > 200) { // Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (joystickY < -200) { // Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  // --- Left/Right Control (using joystickX from V1) ---
  else if (joystickX > 200) { // Right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if (joystickX < -200) { // Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else { // Stop (if both are near zero)
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

// BLYNK_WRITE handler for V0 (Y-axis for Forward/Backward)
BLYNK_WRITE(V0)
{
  joystickY = param.asInt(); // Get the single integer value for Y-axis
  Serial.print("V0 (Y-axis) received: ");
  Serial.println(joystickY);
  moveCar(); // Call moveCar after updating Y
}

// BLYNK_WRITE handler for V1 (X-axis for Left/Right)
BLYNK_WRITE(V1)
{
  joystickX = param.asInt(); // Get the single integer value for X-axis
  Serial.print("V1 (X-axis) received: ");
  Serial.println(joystickX);
  moveCar(); // Call moveCar after updating X
}

void loop()
{
  Blynk.run();
}
