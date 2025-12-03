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
  int ldrDer = 1223 - ldrDerRaw; // invertimos y restamos 200 extra que tiene la ldr

  int dif = ldrIzq - ldrDer;

  if (abs(dif) > 50) { // zona muerta
    if (dif > 0) {
      angulo += 12; // mover hacia izquierda
    } else {
      angulo -= 12; // mover hacia derecha
    }
    angulo = constrain(angulo, 10, 170);
    servo.write(angulo);
  }

  //lecturas 
  Serial.println("------------------------");
  Serial.print("Izq: "); Serial.println(ldrIzq);
  Serial.print(" Der: "); Serial.println(ldrDer);
  Serial.print(" Dif: "); Serial.println(dif);
  Serial.print(" Angulo: "); Serial.println(angulo);
  delay(5000);
}


