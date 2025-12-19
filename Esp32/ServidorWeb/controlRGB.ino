#include <WiFi.h>

// Datos de tu red WiFi
const char* ssid = "ssid";
const char* password = "password";

WiFiServer server(80);

// Pines del LED RGB
const int redPin = 15;
const int greenPin = 16;
const int bluePin = 17;

// Canales PWM
const int freq = 5000;
const int resolution = 8; // 8 bits (0-255)
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;

void setup() {
  Serial.begin(115200);

  // Configurar PWM
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);

  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);

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

    // Extraer valores RGB desde la URL
    int r = getValue(request, "R");
    int g = getValue(request, "G");
    int b = getValue(request, "B");

    if (r >= 0 && g >= 0 && b >= 0) {
      ledcWrite(redChannel, r);
      ledcWrite(greenChannel, g);
      ledcWrite(blueChannel, b);
      Serial.printf("Color -> R:%d G:%d B:%d\n", r, g, b);
    }

    // Respuesta HTML con sliders
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head><title>RGB ESP32</title></head><body>");
    client.println("<h1>Control RGB</h1>");
    client.println("<form action=\"/\">");
    client.println("Rojo: <input type=\"range\" min=\"0\" max=\"255\" name=\"R\"><br>");
    client.println("Verde: <input type=\"range\" min=\"0\" max=\"255\" name=\"G\"><br>");
    client.println("Azul: <input type=\"range\" min=\"0\" max=\"255\" name=\"B\"><br>");
    client.println("<input type=\"submit\" value=\"Enviar\">");
    client.println("</form>");
    client.println("</body></html>");

    client.stop();
  }
}

// Función para obtener valores desde la URL
int getValue(String request, String key) {
  int pos = request.indexOf(key + "=");
  if (pos == -1) return -1;
  int start = pos + key.length() + 1;
  int end = request.indexOf(" ", start);
  if (end == -1) end = request.length();
  return request.substring(start, end).toInt();
}
