#include <WiFi.h>

// Datos de tu red WiFi
const char* ssid = "ssid";
const char* password = "password";

WiFiServer server(80);

const int ledPin = 13; // led a encender

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

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

    String request = client.readStringUntil('\n');
    Serial.println(request);

    if (request.indexOf("GET /LED=ON") != -1) {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido");
    }
    if (request.indexOf("GET /LED=OFF") != -1) {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado");
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head><title>LED ESP32</title></head><body>");
    client.println("<h1>Control del LED</h1>");
    client.println("<p><a href=\"/LED=ON\"><button>Encender LED</button></a></p>");
    client.println("<p><a href=\"/LED=OFF\"><button>Apagar LED</button></a></p>");
    client.println("</body></html>");

    client.stop();
  }
}
