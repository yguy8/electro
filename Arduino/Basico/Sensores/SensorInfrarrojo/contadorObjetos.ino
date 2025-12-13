const int sensorPin = 8;   // Pin del sensor infrarrojo
int contador = 0;
bool estadoAnterior = HIGH; // estado previo del haz

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  Serial.println("Contador iniciado. Esperando objetos...");
}

void loop() {
  int valor = digitalRead(sensorPin);

  // Detectar transición de HIGH -> LOW (cuando se interrumpe el haz)
  if (estadoAnterior == HIGH && valor == LOW) {
    contador++;
//Serial.print("Objeto detectado. Contador = ");
    Serial.println(contador);
  }

  estadoAnterior = valor;
}

