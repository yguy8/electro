//Envia (emisor)

#define RXD2 16
#define TXD2 17
#define LED_SEND 4
#define LED_RECV 5

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(LED_SEND, OUTPUT);
  pinMode(LED_RECV, OUTPUT);
}

void loop() {
  // Enviar mensaje
  digitalWrite(LED_SEND, HIGH);   // LED azul encendido
  Serial2.println("Hola desde ESP32 #1");
  delay(200);                     // breve confirmación
  digitalWrite(LED_SEND, LOW);

  // Revisar si recibió algo
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Recibido: " + data);
    digitalWrite(LED_RECV, HIGH); // LED verde encendido
    delay(200);
    digitalWrite(LED_RECV, LOW);
  }

  delay(2000);
}
