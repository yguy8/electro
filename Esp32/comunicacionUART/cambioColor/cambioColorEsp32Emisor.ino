//emisor Esp32 #1
#define RXD2 22
#define TXD2 23
#define RGB_PIN 16

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  rgbLedWrite(RGB_PIN, 0, 0, 0);

  // Primer mensaje de conexión
  Serial2.println("Conectado a ESP32 #1");
}

void loop() {
  // Revisar si hay datos recibidos desde ESP32 #2
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Recibido: " + data);

    // Interpretar comandos de color
    if (data == "RED") {
      rgbLedWrite(RGB_PIN, 255, 0, 0);
    } else if (data == "GREEN") {
      rgbLedWrite(RGB_PIN, 0, 255, 0);
    } else if (data == "BLUE") {
      rgbLedWrite(RGB_PIN, 0, 0, 255);
    }
  }

  // Revisar si el usuario escribió algo en el monitor serial
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim(); // quitar espacios

    // Enviar comando al ESP32 #2
    Serial2.println(cmd);
    Serial.println("Enviado: " + cmd);
  }
}
