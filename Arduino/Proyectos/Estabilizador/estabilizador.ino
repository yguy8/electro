#include <Servo.h>

// Definición de pines
const int servoPin1 = 6;
const int servoPin2 = 5;
const int sensorPin = 7;
const int buzzPin   = 2;

// Objetos servo
Servo servo1;
Servo servo2;

void setup() {
  // Inicializar servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Configurar pines
  pinMode(sensorPin, INPUT);
  pinMode(buzzPin, OUTPUT);

  // Posición inicial de los servos
  servo1.write(90);
  servo2.write(90);
}

void loop() {
  // Leer sensor de inclinación (digital: HIGH/LOW)
  int inclinacion = digitalRead(sensorPin);

  if (inclinacion == HIGH) {
    // Si está inclinado → activar buzzer
    digitalWrite(buzzPin, HIGH);

    // Ajustar servos para estabilizar
    servo1.write(30);   // mueve un poco hacia un lado
    servo2.write(150);  // mueve hacia el otro
  } else {
    // Si está estable → apagar buzzer
    digitalWrite(buzzPin, LOW);

    // Regresar servos a posición neutra
    servo1.write(90);
    servo2.write(90);
  }

  delay(100); // pequeña pausa para estabilidad
}
