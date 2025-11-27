const int sensorPin = 7;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int inclinacion = digitalRead(sensorPin);

  if (inclinacion == HIGH) {
    Serial.println("INCLINADO");
  } else {
    Serial.println("ESTABLE");
  }

  delay(1000);
}
