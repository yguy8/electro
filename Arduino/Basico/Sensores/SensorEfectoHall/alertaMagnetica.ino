// Sensor Hall con LEDs y buzzer (pitido corto)
const int pinSensor = 2;   // Sensor Hall en pin 2
const int ledRojo = 8;     // LED rojo
const int ledVerde = 9;    // LED verde
const int buzzer = 10;     // Buzzer

void setup() {
  pinMode(pinSensor, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int estadoSensor = digitalRead(pinSensor);

  if (estadoSensor == HIGH) {
    // Imán detectado → LED rojo encendido + pitido corto
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledVerde, LOW);

    digitalWrite(buzzer, HIGH);   // Activa buzzer
    delay(100);                   // Duración del pitido (100 ms)
    digitalWrite(buzzer, LOW);    // Apaga buzzer
  } else {
    // Sin imán → LED verde encendido
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(buzzer, LOW);    // Buzzer apagado
  }

  delay(50); // Pequeña pausa para estabilidad
}
