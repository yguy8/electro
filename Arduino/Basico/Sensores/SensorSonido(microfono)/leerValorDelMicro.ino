int micPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int valorSonido = analogRead(micPin);
  // Serial.println(valorSonido);
  // delay(1500);

  // Lecturas en monitor serial
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "leer") {
      Serial.println("------------------------");
      Serial.print("Valor: "); Serial.println(valorSonido);
      
    }
  }
}
