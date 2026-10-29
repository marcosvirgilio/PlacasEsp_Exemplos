#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Zitta Maker";
const char* password = "#2023makerzitta";

const int trigPin = 5;
const int echoPin = 18;

#define VELOCIDADE_SOM 0.034

long duracao;
float distancia;

WebServer server(80); // Porta padrão HTTP

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Define o manipulador da página principal
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  medirDistancia();

  String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='2'/>"
                "<title>Sensor Ultrassônico</title></head><body>"
                "<h1>Distancia medida</h1>"
                "<p><strong>";
  html += distancia;
  html += " cm</strong></p></body></html>";

  server.send(200, "text/html", html);
}

void medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * VELOCIDADE_SOM / 2;

  Serial.print("Distancia (cm): ");
  Serial.println(distancia);
}
