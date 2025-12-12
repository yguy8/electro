const int sensorPin = 8;   // Pin del sensor 
const int redPin    = 11;  // Pin para el color rojo del LED RGB
const int greenPin  = 10;  // Pin para el color verde del LED RGB
const int bluePin   = 9;   // Pin para el color azul del LED RGB

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  // Configurar los pines del LED RGB como salida
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int valor = digitalRead(sensorPin);

  if (valor == HIGH) {
    Serial.println("Zona despejada");
    // Apagar el LED
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else {
    Serial.println("Obstaculo detectado");
    // Encender el LED en naranja (R=255, G=45, B=0)
    analogWrite(redPin, 255);
    analogWrite(greenPin, 45);
    analogWrite(bluePin, 0);
  }
}
