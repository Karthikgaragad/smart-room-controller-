// Pin definitions
const int pirAnalogPin = A1;   // Analog PIR output
const int lm35Pin = A0;

const int relayFan = 3;
const int relayBulb = 4;

// Relay logic (ACTIVE LOW)
#define ON LOW
#define OFF HIGH

// Threshold for motion detection (tune this!)
int threshold = 300;

void setup() {
  pinMode(relayFan, OUTPUT);
  pinMode(relayBulb, OUTPUT);

  digitalWrite(relayFan, OFF);
  digitalWrite(relayBulb, OFF);

  Serial.begin(9600);
}

void loop() {

  // Read PIR analog value
  int pirValue = analogRead(pirAnalogPin);

  // Read temperature
  int tempVal = analogRead(lm35Pin);
  float voltage = tempVal * (5.0 / 1023.0);
  float temperature = voltage * 100;

  Serial.print("PIR Value: ");
  Serial.print(pirValue);
  Serial.print("  Temp: ");
  Serial.println(temperature);

  // Motion detection using threshold
  if (pirValue > threshold) {
    // Motion detected
    digitalWrite(relayBulb, ON);

    if (temperature > 25) {
      digitalWrite(relayFan, ON);
    } else {
      digitalWrite(relayFan, OFF);
    }

  } else {
    // No motion
    digitalWrite(relayBulb, OFF);
    digitalWrite(relayFan, OFF);
  }

  delay(500);
}