const int pinLdrIzq = A0;
const int pinLdrDer = A1;

void setup() {
  Serial.begin(9600); // Inicia comunicación serial
}

void loop() {
  int valorIzq = analogRead(pinLdrIzq); // Lee LDR izquierda
  int valorDer = analogRead(pinLdrDer); // Lee LDR derecha

  // Imprime valores en el monitor serial
  Serial.print("LDR Izquierda: ");
  Serial.print(valorIzq);
  Serial.print(" | LDR Derecha: ");
  Serial.println(valorDer);

  delay(500); // medio segundo entre lecturas
}
