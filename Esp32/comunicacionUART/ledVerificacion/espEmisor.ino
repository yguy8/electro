// Emisor ESP32 #1

#define RXD2 3
#define TXD2 1
#define RGB_PIN 16

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  // Apagar LED al inicio
  rgbLedWrite(RGB_PIN, 0, 0, 0);
}

void loop() {
  // Enviar mensaje
  rgbLedWrite(RGB_PIN, 0, 0, 255);   // Azul para envío
  Serial2.println("Hola desde ESP32 #1");
  delay(300);
  rgbLedWrite(RGB_PIN, 0, 0, 0);

  // Revisar si recibió algo
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Recibido: " + data);

    // LED verde para indicar recepción
    rgbLedWrite(RGB_PIN, 0, 255, 0);
    delay(300);
    rgbLedWrite(RGB_PIN, 0, 0, 0);
  }

  delay(2000); // Pausa entre envíos
}
