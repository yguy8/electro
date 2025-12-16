#include <ESP32Servo.h>

Servo myServo; // Crea objeto servo

void setup() {
  myServo.attach(13); // Conecta el servo al pin GPIO 13
}

void loop() {
  myServo.write(0);   // Mueve a 0 grados
  delay(1000);
  myServo.write(90);  // Mueve a 90 grados
  delay(1000);
  myServo.write(180); // Mueve a 180 grados
  delay(1000);
}
