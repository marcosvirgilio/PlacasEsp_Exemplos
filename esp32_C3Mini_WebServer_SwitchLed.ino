#include <WiFi.h>
#include <WebServer.h>

// Novos dados da rede Wi-Fi
const char* ssid = "mvc";
const char* password = "valentina";

// Pino do LED Onboard no ESP32-C3 Super Mini
const int LED_PIN = 8;

WebServer server(80);

// Função que constrói e envia a página HTML
void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; margin-top: 50px; background-color: #f4f4f4; }";
  html += "h1 { color: #333; }";
  html += ".btn { display: inline-block; padding: 15px 30px; font-size: 20px; text-decoration: none; color: white; border-radius: 5px; margin: 10px; }";
  html += ".btn-on { background-color: #28a745; }";
  html += ".btn-off { background-color: #dc3545; }";
  html += "</style></head>";
  html += "<body>";
  html += "<h1>ESP32-C3 - Rede MVC</h1>";
  html += "<p>Controle do LED Onboard</p>";
  html += "<a href=\"/led/on\" class=\"btn btn-on\">LIGAR LED</a>";
  html += "<a href=\"/led/off\" class=\"btn btn-off\">DESLIGAR LED</a>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleLedOn() {
  digitalWrite(LED_PIN, LOW); // LOW acende
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLedOff() {
  digitalWrite(LED_PIN, HIGH); // HIGH apaga
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Configura o pino do LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Inicializa apagado

  // Conecta à nova rede Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("Conectando ao Wi-Fi mvc");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado com sucesso!");
  Serial.print("Endereço IP obtido via DHCP: ");
  Serial.println(WiFi.localIP());

  // Rotas da aplicação web
  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();
  Serial.println("Servidor Web iniciado!");
}

void loop() {
  server.handleClient();
}