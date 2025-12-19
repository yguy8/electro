#include <WiFi.h>

// Datos de tu red WiFi
const char* ssid = "ssid";
const char* password = "password";

WiFiServer server(80);

const int ledPin = 4; // pin del led a encender
String ledState = "Apagado"; // estado inicial

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
      ledState = "Encendido";
      Serial.println("LED encendido");
    }
    if (request.indexOf("GET /LED=OFF") != -1) {
      digitalWrite(ledPin, LOW);
      ledState = "Apagado";
      Serial.println("LED apagado");
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head><title>LED ESP32</title>");
    client.println("<style>");
    client.println("body { text-align: center; font-family: 'Segoe UI', Arial, sans-serif;");
    client.println("       background: linear-gradient(135deg, #ece9e6, #ffffff); color: #333; }");
    client.println("h1 { font-size: 36px; margin-top: 20px; }");
    client.println("h2 { font-size: 28px; margin-top: 20px; }");
    client.println(".btn { font-size: 24px; padding: 15px 40px; margin: 20px; border: none;");
    client.println("       border-radius: 12px; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; }");
    client.println(".btn:hover { transform: scale(1.05); box-shadow: 0px 4px 12px rgba(0,0,0,0.2); }");
    client.println(".on { background-color: #4CAF50; color: white; }");
    client.println(".on:hover { background-color: #45a049; }");
    client.println(".off { background-color: #f44336; color: white; }");
    client.println(".off:hover { background-color: #d32f2f; }");
    client.println(".estadoOn { color: #4CAF50; font-weight: bold; }");
    client.println(".estadoOff { color: #f44336; font-weight: bold; }");
    client.println("</style></head><body>");
    client.println("<h1>Control del LED</h1>");
    client.println("<p><a href=\"/LED=ON\"><button class=\"btn on\">Encender LED</button></a></p>");
    client.println("<p><a href=\"/LED=OFF\"><button class=\"btn off\">Apagar LED</button></a></p>");

    // Estado dinámico con color
    if (ledState == "Encendido") {
      client.println("<h2>Estado actual: <span class='estadoOn'>Encendido</span></h2>");
    } else {
      client.println("<h2>Estado actual: <span class='estadoOff'>Apagado</span></h2>");
    }

    client.println("</body></html>");
    client.stop();
  }
}
