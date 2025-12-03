#include <Servo.h>

int pinservoIzq = 9;
int pinservoDer = 10;

Servo servoIzq;
Servo servoDer;

int sensorLuz = A0;
int umbral = 500; // Ajusta según la intensidad de luz

void setup() {
  servoIzq.attach(pinservoIzq);
  servoDer.attach(pinservoDer);
  pinMode(sensorLuz, INPUT);
}

void loop() {
  int valorLuz = analogRead(sensorLuz);

  if (valorLuz < umbral) {
    // Si hay luz, mover los servos para simular caminar
    servoIzq.write(40);
    servoDer.write(130);
    delay(500);
    servoIzq.write(130);
    servoDer.write(40);
    delay(500);
  } else {
    // Si no hay luz, detener servos
    servoIzq.write(90);
    servoDer.write(90);
  }
}
