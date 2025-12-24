//encender 3 leds 

#include <WiFi.h>
#include <WebServer.h>

//Configura tu red WiFi
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// Pines de los LEDs
const int led1 = 2;   // Cambia según tu conexión
const int led2 = 4;
const int led3 = 5;

WebServer server(80);

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Control LEDs</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; background: #f0f0f0; }";
  html += "h2 { color: #333; margin-top: 20px; }";
  html += "form { margin-top: 30px; }";
  html += "input[type=submit] {";
  html += "  background-color: #4CAF50;";
  html += "  border: none;";
  html += "  color: white;";
  html += "  padding: 15px 32px;";
  html += "  text-align: center;";
  html += "  text-decoration: none;";
  html += "  display: inline-block;";
  html += "  font-size: 18px;";
  html += "  margin: 10px;";
  html += "  border-radius: 8px;";
  html += "  cursor: pointer;";
  html += "  transition: 0.3s;";
  html += "}";
  html += "input[type=submit]:hover { background-color: #45a049; }";
  html += "</style></head><body>";

  html += "<h2>Control de LEDs por porcentaje</h2>";
  html += "<form action='/set' method='GET'>";
  html += "<input type='submit' name='value' value='0%'>";
  html += "<input type='submit' name='value' value='30%'>";
  html += "<input type='submit' name='value' value='60%'>";
  html += "<input type='submit' name='value' value='100%'>";
  html += "</form>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}


void handleSet() {
  String value = server.arg("value");

  if (value == "0%") {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else if (value == "30%") {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else if (value == "60%") {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  } else if (value == "100%") {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  server.sendHeader("Location", "/");
  server.send(303); // Redirige a la página principal
}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}
