//Envia (emisor)

#define RXD2 3
#define TXD2 1

void setup() {
  Serial.begin(115200); // Monitor serie
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART2
}

void loop() {
  Serial2.println("Hola desde ESP32 #1");
  delay(1000);
}
