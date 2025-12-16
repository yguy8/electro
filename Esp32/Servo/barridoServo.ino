#include <ESP32Servo.h>

Servo myServo;

const int servoPin = 13;
const int ledVerde = 25;
const int ledAmarillo = 26;
const int ledRojo = 27;

// Límites del barrido
const int minAngle = 10;
const int maxAngle = 170;

// Paso y velocidad
const int stepDeg = 2;     // tamaño del paso
const int stepDelay = 15;  // ms entre pasos

void setup() {
  Serial.begin(115200);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(minAngle); // posición inicial
}

void loop() {
  // Barrido ascendente: 10 -> 170
  for (int angle = minAngle; angle <= maxAngle; angle += stepDeg) {
    actualizarServoYLeds(angle);
    delay(stepDelay);
  }

  // Barrido descendente: 170 -> 10
  for (int angle = maxAngle; angle >= minAngle; angle -= stepDeg) {
    actualizarServoYLeds(angle);
    delay(stepDelay);
  }
}

void actualizarServoYLeds(int angle) {
  myServo.write(angle);

  // Apagar todos
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);

  // Encender según ángulo
  if (angle <= 10) {
    digitalWrite(ledVerde, HIGH);
  } else if (angle >= 85 && angle <= 95) {
    digitalWrite(ledAmarillo, HIGH);
  } else if (angle >= 170) {
    digitalWrite(ledRojo, HIGH);
  }

  Serial.print("Ángulo: ");
  Serial.println(angle);
}
