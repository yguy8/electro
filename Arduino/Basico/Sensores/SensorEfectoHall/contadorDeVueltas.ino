// Contador de vueltas con sensor Hall + LEDs indicador
volatile int contadorVueltas = 0;  

const int pinSensor = 2;   // Sensor Hall en pin 2
const int ledRojo = 8;     // LED rojo
const int ledVerde = 9;    // LED verde

void setup() {
  Serial.begin(9600);

  pinMode(pinSensor, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Interrupción cuando el sensor detecta el imán
  attachInterrupt(digitalPinToInterrupt(pinSensor), contarVuelta, RISING);
}

void loop() {
  // Mostrar vueltas en el monitor serial
  Serial.print("Vueltas: ");
  Serial.println(contadorVueltas);

  // Leer estado del sensor
  int estadoSensor = digitalRead(pinSensor);

  if (estadoSensor == HIGH) {
    // Imán detectado → LED rojo encendido
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledVerde, LOW);
  } else {
    // Sin imán → LED verde encendido
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, HIGH);
  }

  delay(200); // Pequeña pausa para estabilidad
}

// Función de interrupción: suma una vuelta
void contarVuelta() {
  contadorVueltas++;
}
