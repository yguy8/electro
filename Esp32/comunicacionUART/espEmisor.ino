//Envia (emisor)

#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200); // Monitor serie
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART2
}

void loop() {
  Serial2.println("Hola desde ESP32 #1");
  delay(1000);
}
