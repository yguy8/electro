// Joystick
const int joyX = A0;
const int joyY = A1;
const int joyButton = 8;

// LEDs
const int ledAzul = 2;
const int ledRojo = 3;
const int ledVerde = 4;
const int ledAmarillo = 5;
const int ledBlanco = 6;

const int lowThreshold = 300;
const int highThreshold = 700;

void setup() {
  pinMode(ledAzul, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledBlanco, OUTPUT);
  pinMode(joyButton, INPUT_PULLUP);
}

void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int button = digitalRead(joyButton);

  // Apagar todos primero
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledBlanco, LOW);

  // X positivo → Azul
  if (xValue > highThreshold) digitalWrite(ledAzul, HIGH);

  // X negativo → Rojo
  if (xValue < lowThreshold) digitalWrite(ledRojo, HIGH);

  // Y positivo → Verde
  if (yValue > highThreshold) digitalWrite(ledVerde, HIGH);

  // Y negativo → Amarillo
  if (yValue < lowThreshold) digitalWrite(ledAmarillo, HIGH);

  // Botón → Blanco
  if (button == LOW) digitalWrite(ledBlanco, HIGH);
}
