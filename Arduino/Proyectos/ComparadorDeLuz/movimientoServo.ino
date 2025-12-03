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
  int ldrDer = 800 - ldrDerRaw; // inverso correcto esta ajustado porque las
  //ldr no leen el mismo valor una con luz marca 15 y la otra marca 15 con sombra
  //800 es el ajuste porque es la diferencia que existe entre lecturas

  int dif = ldrIzq - ldrDer;

  if (abs(dif) < 20) {
    // Si son iguales o muy cercanos → centro
    angulo = 90;
  } else {
    // Movimiento proporcional
    int ajuste = dif / 40; // factor de sensibilidad
    angulo = constrain(angulo + ajuste, 10, 170);
  }

  servo.write(angulo);

  // Lecturas en monitor serial
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando == "leer") {
      Serial.println("------------------------");
      Serial.print("Izq: "); Serial.println(ldrIzq);
      Serial.print("Der: "); Serial.println(ldrDer);
      Serial.print("Dif: "); Serial.println(dif);
      Serial.print("Angulo: "); Serial.println(angulo);
    }
  }

  delay(100);
}
