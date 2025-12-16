#include <ESP32Servo.h>

Servo myServo;

const int potPin = 34;     // Entrada analógica del potenciómetro
const int ledVerde = 25;   // LED verde
const int ledAmarillo = 26;// LED amarillo
const int ledRojo = 27;    // LED rojo
const int servoPin = 13;   // Servo

void setup() {
  Serial.begin(115200);

  // Configurar LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Configurar servo
  myServo.attach(servoPin);
}

void loop() {
  // Leer potenciómetro (0–4095 en ESP32)
  int potValue = analogRead(potPin);

  // Mapear a ángulo de servo (0–180 grados)
  int angle = map(potValue, 0, 4095, 0, 180);

  // Mover servo
  myServo.write(angle);

  // Apagar todos los LEDs
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);

  // Encender LED según ángulo
  if (angle <= 10) {
    digitalWrite(ledVerde, HIGH);
  } else if (angle <= 90 ) {
    digitalWrite(ledAmarillo, HIGH);
  } else if (angle >= 170) {
    digitalWrite(ledRojo, HIGH);
  }

  // Mostrar ángulo en monitor serie
  Serial.print("Ángulo: ");
  Serial.println(angle);

  delay(50); // Pequeño retardo para estabilidad
}
