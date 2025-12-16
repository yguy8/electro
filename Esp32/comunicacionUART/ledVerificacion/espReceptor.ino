// Receptor ESP32 #2

#define RXD2 22
#define TXD2 23
#define RGB_PIN 16

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  // Apagar LED al inicio
  rgbLedWrite(RGB_PIN, 0, 0, 0);
}

void loop() {
  // Revisar si recibió algo
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Recibido: " + data);

    // LED verde para indicar recepción
    rgbLedWrite(RGB_PIN, 0, 255, 0);
    delay(300);
    rgbLedWrite(RGB_PIN, 0, 0, 0);

    // Responder
    rgbLedWrite(RGB_PIN, 0, 0, 255); // Azul para envío
    Serial2.println("Hola ESP32 #1, recibido!");
    delay(300);
    rgbLedWrite(RGB_PIN, 0, 0, 0);
  }
}
