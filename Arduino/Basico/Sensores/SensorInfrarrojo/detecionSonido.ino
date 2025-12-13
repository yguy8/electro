const int sensorPin = A0;   // Pin analógico del sensor IR
const int buzzerPin = 9;    // Pin del buzzer

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int valor = analogRead(sensorPin); // lectura entre 0 y 1023
  // Serial.print("Valor sensor: ");
  // Serial.println(valor);

  // Mapear distancia a frecuencia (ajusta según tu sensor)
  int frecuencia = map(valor, 100, 600, 800, 1000); 
  // rango de frecuencias: 800 Hz a 1000 Hz

  // Generar tono en el buzzer
  tone(buzzerPin, frecuencia, 20); // tono corto de 20 ms

  delay(50); // pequeño retardo para estabilidad
}
