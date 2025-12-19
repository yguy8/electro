#include <WiFi.h>

// Datos de tu red WiFi
const char* ssid = "TuSSID";
const char* password = "TuPassword";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());

  // Inicia servidor
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Espera clientes
  if (client) {
    Serial.println("Cliente conectado");
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<h1>Hola desde ESP32!</h1>");
    client.println();
    client.stop();
  }
}
