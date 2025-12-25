#include <Servo.h>

Servo servo1;  // Servo en pin 9
Servo servo2;  // Servo en pin 10

const int sensorPin = 2;   // Pin donde conectas el OUT del TTP223
bool estado = false;       // Estado: false = cerrado, true = abierto

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10);
  pinMode(sensorPin, INPUT);

  // Posición inicial
  servo1.write(0);
  servo2.write(85);
  Serial.println("Sistema listo. Toca el pulsador para alternar entre abierto/cerrado.");
}

void loop() {
  if (digitalRead(sensorPin) == HIGH) {
    delay(200); // Pequeño debounce para evitar rebotes
    estado = !estado; // Cambia el estado

    if (estado) {
      // Estado abierto
      servo1.write(85);
      servo2.write(0);
      Serial.println("Estado: ABIERTO");
    } else {
      // Estado cerrado
      servo1.write(0);
      servo2.write(85);
      Serial.println("Estado: CERRADO");
    }

    // Espera a que se suelte el pulsador antes de continuar
    while (digitalRead(sensorPin) == HIGH) {
      delay(10);
    }
  }
}
