#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>   

// Configuración WiFi
const char* ssid = "";
const char* password = "";

// URL de API de clima OpenMeteo usada 
String url = ""

WebServer server(80);
String climaHTML = "<h1>Esperando datos...</h1>";

// Función para traducir weather_code
String weatherDescription(int code) {
  switch(code) {
    case 0: return "Soleado ☀️";
    case 1: return "Mayormente soleado 🌤️";
    case 2: return "Parcialmente nublado ⛅";
    case 3: return "Nublado ☁️";
    case 45: case 48: return "Niebla 🌫️";
    case 51: case 53: case 55: return "Llovizna 🌦️";
    case 61: return "Lluvia ligera 🌧️";
    case 63: return "Lluvia moderada 🌧️";
    case 65: return "Lluvia intensa 🌧️";
    case 71: case 73: case 75: return "Nieve ❄️";
    case 80: return "Chubascos ligeros 🌦️";
    case 81: return "Chubascos moderados 🌧️";
    case 82: return "Chubascos fuertes 🌧️";
    case 95: return "Tormenta eléctrica ⛈️";
    case 96: case 99: return "Tormenta con granizo 🌩️";
    default: return "Condición desconocida";
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Conectado a WiFi");
  Serial.print("📡 IP del ESP32: ");
  Serial.println(WiFi.localIP());

  // Iniciar mDNS con nombre "clima"
  if (MDNS.begin("clima")) {
    Serial.println("🌐 mDNS iniciado: http://clima.local/");//nombre del dominio de la red local
  } else {
    Serial.println("⚠️ Error iniciando mDNS");
  }

  // Ruta principal
  server.on("/", [&]() {
    server.send(200, "text/html", climaHTML);
  });
  server.begin();
}

void loop() {
  server.handleClient();
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 3600000 || lastUpdate == 0) {
    actualizarClima();
    lastUpdate = millis();
  }
}

void actualizarClima() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      StaticJsonDocument<8192> doc;
      if (deserializeJson(doc, payload) == DeserializationError::Ok) {
        
        // Datos actuales
        float temp = doc["current"]["temperature_2m"];
        float apparent = doc["current"]["apparent_temperature"];
        int humidity = doc["current"]["relative_humidity_2m"];
        int weatherCode = doc["current"]["weather_code"];
        float windGust = doc["current"]["wind_gusts_10m"];
        float pressure = doc["current"]["surface_pressure"];

        // Datos diarios
        float tempMax = doc["daily"]["temperature_2m_max"][0];
        float tempMin = doc["daily"]["temperature_2m_min"][0];
        int precipProb = doc["daily"]["precipitation_probability_max"][0];
        int weatherDaily = doc["daily"]["weather_code"][0];
        String sunrise = doc["daily"]["sunrise"][0];
        String sunset = doc["daily"]["sunset"][0];
        float uvMax = doc["daily"]["uv_index_max"][0];
        float windMax = doc["daily"]["wind_gusts_10m_max"][0];

        // Construir HTML con CSS mejorado
        climaHTML = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Clima ESP32</title>"
                    "<style>"
                    "body{font-family:'Segoe UI',Tahoma,sans-serif;background:linear-gradient(to right,#e0f7fa,#f1f8e9);color:#333;margin:0;padding:20px;}"
                    "h1{color:#00695c;margin-bottom:10px;}h2{color:#00796b;margin-top:30px;}"
                    "table{margin:20px auto;border-collapse:collapse;width:90%;box-shadow:0 4px 8px rgba(0,0,0,0.1);background:#fff;border-radius:8px;overflow:hidden;}"
                    "th{background:#004d40;color:#fff;padding:12px;}td{padding:10px;border-bottom:1px solid #ddd;}tr:nth-child(even){background:#f9f9f9;}tr:hover{background:#e0f2f1;}"
                    "</style></head><body>";
        climaHTML += "<h1>🌦️ Panel del clima - San Julián</h1>";

        // Datos actuales
        climaHTML += "<h2>⏱️ Datos actuales</h2><table>";
        climaHTML += "<tr><th>Variable</th><th>Valor</th></tr>";
        climaHTML += "<tr><td>Temperatura</td><td>" + String(temp) + " °C</td></tr>";
        climaHTML += "<tr><td>Temperatura aparente</td><td>" + String(apparent) + " °C</td></tr>";
        climaHTML += "<tr><td>Humedad relativa</td><td>" + String(humidity) + " %</td></tr>";
        climaHTML += "<tr><td>Condición</td><td>" + weatherDescription(weatherCode) + "</td></tr>";
        climaHTML += "<tr><td>Ráfagas de viento</td><td>" + String(windGust) + " km/h</td></tr>";
        climaHTML += "<tr><td>Presión superficial</td><td>" + String(pressure) + " hPa</td></tr>";
        climaHTML += "</table>";

        // Pronóstico diario
        climaHTML += "<h2>📅 Pronóstico diario</h2><table>";
        climaHTML += "<tr><th>Variable</th><th>Valor</th></tr>";
        climaHTML += "<tr><td>Temperatura máxima</td><td>" + String(tempMax) + " °C</td></tr>";
        climaHTML += "<tr><td>Temperatura mínima</td><td>" + String(tempMin) + " °C</td></tr>";
        climaHTML += "<tr><td>Probabilidad de precipitación</td><td>" + String(precipProb) + " %</td></tr>";
        climaHTML += "<tr><td>Condición</td><td>" + weatherDescription(weatherDaily) + "</td></tr>";
        climaHTML += "<tr><td>Salida del sol</td><td>" + sunrise + "</td></tr>";
        climaHTML += "<tr><td>Puesta del sol</td><td>" + sunset + "</td></tr>";
        climaHTML += "<tr><td>Índice UV máximo</td><td>" + String(uvMax) + "</td></tr>";
        climaHTML += "<tr><td>Ráfagas de viento máximas</td><td>" + String(windMax) + " km/h</td></tr>";
        climaHTML += "</table>";

        climaHTML += "</body></html>";
      }
    }
    http.end();
  }
}
