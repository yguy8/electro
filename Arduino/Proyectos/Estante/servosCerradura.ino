#include <Servo.h>

Servo servo1;  // Servo en pin 9
Servo servo2;  // Servo en pin 10

void setup() {
  Serial.begin(9600);   // Inicia comunicación serial
  servo1.attach(9);     // Conecta servo1 al pin 9
  servo2.attach(10);    // Conecta servo2 al pin 10

  // Posición inicial
  servo1.write(0);
  servo2.write(0);

  Serial.println("Escribe 'abierto' o 'cerrado' en el monitor serial:");
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n'); // Lee hasta Enter
    comando.trim(); // Elimina espacios o saltos extra

    if (comando.equalsIgnoreCase("abierto")) {
      servo1.write(85);  // Pin 9 a 85°
      servo2.write(0);   // Pin 10 a 0°
      Serial.println("Estado: ABIERTO");
    } 
    else if (comando.equalsIgnoreCase("cerrado")) {
      servo1.write(0);   // Pin 9 a 0°
      servo2.write(85);  // Pin 10 a 85°
      Serial.println("Estado: CERRADO");
    } 
    else {
      Serial.println("Comando no reconocido. Usa 'abierto' o 'cerrado'.");
    }
  }
}
