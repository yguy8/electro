#include <Servo.h>

// Pines
const int servoPin1 = 5;
const int servoPin2 = 6;
const int rainSensorPin = 3;

// Objetos servo
Servo servo1;
Servo servo2;

void setup() {
  // Inicializar servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Configurar sensor
  pinMode(rainSensorPin, INPUT);

  // Posición inicial (reposo)
  servo1.write(90);
  servo2.write(90);
}

void loop() {
  int lluvia = digitalRead(rainSensorPin);

  if (lluvia == LOW) { //lógica invertida LOW es cuando esta lloviendo
    // Si hay lluvia → mover limpiaparabrisas
    limpiarParabrisas();
  } else {
    // Si no hay lluvia → reposo
    servo1.write(10);//servo del pin 5 que es la derecha
    servo2.write(170); //servo del pin 6 que es la izquierda
  }
}

// Función para simular movimiento de limpiaparabrisas
void limpiarParabrisas() {
  // Barrido hacia un lado
  for (int ang = 30; ang <= 140; ang++) {
    servo1.write(ang);
    servo2.write(180 - ang); // movimiento inverso
    delay(15);
  }

  // Barrido hacia el otro lado
  for (int ang = 140; ang >= 30; ang--) {
    servo1.write(ang);
    servo2.write(180 - ang);
    delay(15);
  }
}
