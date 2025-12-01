#include <Servo.h>

Servo servo;
const int pinLDR = A0;
const int pinServo = 9;

void setup() {
  servo.attach(pinServo);
}

void loop() {
  int lectura = analogRead(pinLDR);   // 0–1023
  int angulo = map(lectura, 0, 1023, 10, 170);
  servo.write(angulo);
  //delay(20);
}
