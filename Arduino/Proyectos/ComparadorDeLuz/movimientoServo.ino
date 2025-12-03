#include <Servo.h>

const int pinServo = 3;
const int pinLdrIzq = A0;
const int pinLdrDer = A1;

Servo servo;
int angulo = 90; // posición inicial

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  servo.write(angulo);
}

void loop() {
  int ldrIzq = analogRead(pinLdrIzq);
  int ldrDerRaw = analogRead(pinLdrDer);
  int ldrDer = 1023 - ldrDerRaw; // invertimos

  int dif = ldrIzq - ldrDer;

  if (abs(dif) > 50) { // zona muerta
    if (dif > 0) {
      angulo += 2; // mover hacia izquierda
    } else {
      angulo -= 2; // mover hacia derecha
    }
    angulo = constrain(angulo, 10, 170);
    servo.write(angulo);
  }

  // Serial.print("Izq: "); Serial.print(ldrIzq);
  // Serial.print(" Der: "); Serial.print(ldrDer);
  // Serial.print(" Dif: "); Serial.print(dif);
  // Serial.print(" Angulo: "); Serial.println(angulo);

  delay(100);
}
