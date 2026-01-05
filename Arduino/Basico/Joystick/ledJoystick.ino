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
  if (xValue > 550) digitalWrite(ledAzul, HIGH);

  // X negativo → Rojo
  if (xValue < 10) digitalWrite(ledRojo, HIGH);

  // Y positivo → Verde
  if (yValue > 550) digitalWrite(ledVerde, HIGH);

  // Y negativo → Amarillo
  if (yValue < 10) digitalWrite(ledBlanco, HIGH);

  // Botón → Blanco
  if (button == LOW) digitalWrite(ledAmarillo, HIGH);
}

//esta medio extraño como funciono pero funciono
