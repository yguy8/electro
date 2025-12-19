#include <WiFi.h>

// Datos de tu red WiFi
const char* ssid = "TuSSID";
const char* password = "TuPassword";

WiFiServer server(80);

const int ledPin = 2; // Pin donde está conectado el LED

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED apagado al inicio

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected() && !client.available()) {
      delay(1);
    }

    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Control del LED según la URL
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, HIGH);
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, LOW);
    }

    // Página HTML con botones
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head><title>Control LED ESP32</title>");
    client.println("<style>");
    client.println("body { font-family: Arial; text-align: center; background-color: #f0f0f0; }");
    client.println("h1 { color: #007BFF; }");
    client.println("button { padding: 15px 30px; font-size: 18px; margin: 10px; border: none; border-radius: 5px; cursor: pointer; }");
    client.println(".on { background-color: green; color: white; }");
    client.println(".off { background-color: red; color: white; }");
    client.println("</style></head>");
    client.println("<body>");
    client.println("<h1>Control del LED</h1>");
    client.println("<p><a href=\"/LED=ON\"><button class='on'>Encender LED</button></a></p>");
    client.println("<p><a href=\"/LED=OFF\"><button class='off'>Apagar LED</button></a></p>");
    client.println("</body></html>");

    client.stop();
  }
}
