// LED RGB integrado en GPIO16
#define RGB_PIN 16

void setup() {
  // No es necesario configurar pinMode para el RGB integrado
}

void loop() {
  // Blanco
  rgbLedWrite(RGB_PIN, 255, 255, 255);
  delay(1000);

  // Rojo
  rgbLedWrite(RGB_PIN, 255, 0, 0);
  delay(1000);

  // Verde
  rgbLedWrite(RGB_PIN, 0, 255, 0);
  delay(1000);

  // Azul
  rgbLedWrite(RGB_PIN, 0, 0, 255);
  delay(1000);

  // Apagado
  rgbLedWrite(RGB_PIN, 0, 0, 0);
  delay(1000);
}
