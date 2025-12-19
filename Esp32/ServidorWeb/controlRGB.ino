#include <WiFi.h>

// Datos de tu red WiFi
const char* ssid = "ssid";
const char* password = "password";

WiFiServer server(80);

// Pines del LED RGB
const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;

void setup() {
  Serial.begin(115200);

  // Configurar pines como salida
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

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
      analogWrite(redPin, r);
      analogWrite(greenPin, g);
      analogWrite(bluePin, b);
      Serial.printf("Color -> R:%d G:%d B:%d\n", r, g, b);
    }

    // Respuesta HTML con sliders mejorados
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head><title>RGB ESP32</title>");
    client.println("<style>");
    client.println("body { font-family: Arial; text-align: center; background: #f0f0f0; }");
    client.println("h1 { color: #333; }");
    client.println(".slider { width: 300px; }");
    client.println(".color-box { width: 150px; height: 150px; margin: 20px auto; border: 2px solid #333; }");
    client.println("</style>");
    client.println("<script>");
    client.println("function updateColor() {");
    client.println("  var r = document.getElementById('R').value;");
    client.println("  var g = document.getElementById('G').value;");
    client.println("  var b = document.getElementById('B').value;");
    client.println("  document.getElementById('colorBox').style.backgroundColor = 'rgb(' + r + ',' + g + ',' + b + ')';");
    client.println("}");
    client.println("</script>");
    client.println("</head><body>");
    client.println("<h1>Control RGB ESP32</h1>");
    client.println("<div id='colorBox' class='color-box'></div>");
    client.println("<form action=\"/\" method=\"GET\">");
    client.println("Rojo: <input type=\"range\" min=\"0\" max=\"255\" id=\"R\" name=\"R\" class=\"slider\" oninput=\"updateColor()\"><br>");
    client.println("Verde: <input type=\"range\" min=\"0\" max=\"255\" id=\"G\" name=\"G\" class=\"slider\" oninput=\"updateColor()\"><br>");
    client.println("Azul: <input type=\"range\" min=\"0\" max=\"255\" id=\"B\" name=\"B\" class=\"slider\" oninput=\"updateColor()\"><br><br>");
    client.println("<input type=\"submit\" value=\"Aplicar Color\">");
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
