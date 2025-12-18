const int ledPin = 5;   // LED en GPIO 5
const int potPin = 34;  // Potenciómetro en GPIO 34

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);       // 0–4095
  int ledValue = map(potValue, 0, 4095, 0, 255);
  analogWrite(ledPin, ledValue);           // controla brillo del LED
}
