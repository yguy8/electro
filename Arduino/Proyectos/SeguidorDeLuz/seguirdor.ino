//esta es la versión con dos ldr que compara las lecturas
#include <Servo.h>

Servo servo;
const int ldrLeft = A0;
const int ldrRight = A1;
const int pinServo = 9;

int angle = 90;          // posición inicial
const int step = 2;      // paso de movimiento
const int minAngle = 0;
const int maxAngle = 180;
const int deadZone = 20; // umbral para evitar temblores

void setup() {
  servo.attach(pinServo);
  servo.write(angle);
}

void loop() {
  int left = analogRead(ldrLeft);
  int right = analogRead(ldrRight);

  int diff = left - right;

  if (abs(diff) > deadZone) {
    if (diff > 0) {
      angle -= step; // más luz a la izquierda → gira izquierda
    } else {
      angle += step; // más luz a la derecha → gira derecha
    }
    angle = constrain(angle, minAngle, maxAngle);
    servo.write(angle);
  }

  delay(30); // pequeño retardo para suavizar
}
