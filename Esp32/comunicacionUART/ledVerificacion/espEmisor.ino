#define RXD2 22
#define TXD2 23
#define RGB_PIN 16

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Apagar LED al inicio
  rgbLedWrite(RGB_PIN, 0, 0, 0);
}

void loop() {
  // Enviar mensaje
  rgbLedWrite(RGB_PIN, 0, 0, 255);   // Azul
  Serial2.println("Hola desde ESP32 #1");
  delay(200);
  rgbLedWrite(RGB_PIN, 0, 0, 0);     // Apagar

  // Revisar si recibió algo
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Recibido: " + data);

    rgbLedWrite(RGB_PIN, 0, 255, 0); // Verde
    delay(200);
    rgbLedWrite(RGB_PIN, 0, 0, 0);   // Apagar
  }

  delay(2000);
}
