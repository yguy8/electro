#include <Servo.h>

Servo miServo;
int pinMicrofono = A0;   // Entrada mic
int pinServo = 9;        // Pin del servo
int umbral = 300;        // Sensibilidad del micrófono
bool estadoServo = false; // false = 30°, true = 115°

void setup() {
  Serial.begin(9600);
  miServo.attach(pinServo);
  miServo.write(30);     // Posición inicial
}

void loop() {
  int valorSonido = analogRead(pinMicrofono);
  Serial.println(valorSonido);

  if (valorSonido > umbral) {
    // Cambia el estado del servo
    estadoServo = !estadoServo;

    if (estadoServo) {
      miServo.write(115);  
    } else {
      miServo.write(30);   
    }

    delay(500); // Pausa para evitar múltiples detecciones del mismo ruido
  }
}
