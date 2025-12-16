//parpadear el led del GPIO 2, el led esta integrado con la placa

#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // LED encendido
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);  // LED apagado
  delay(1000);
}
