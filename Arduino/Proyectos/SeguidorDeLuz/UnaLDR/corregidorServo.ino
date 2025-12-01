#include <Servo.h>
Servo servo;

void setup() {
  servo.attach(9);   // pin de señal
}

void loop() {
  // manda el angulo 0, 90, 170, 90 7 así haciendo un escaneo para verificar su función
  servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(170);
  delay(1000);
  servo.write(90);
  delay(1000);
}
