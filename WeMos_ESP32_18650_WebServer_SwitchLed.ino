#include <WiFi.h>

// Credenciais da rede
const char* ssid     = "IFSC";
const char* password = "campuschapeco";

// Porta padrão para o Servidor Web
WiFiServer server(80);

// Pino do LED embutido (GPIO 16)
const int pinoLed = 16;

// Variável para armazenar o estado atual do LED (iniciando explicitamente como LIGADO)
String estadoLed = "LIGADO";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configura o pino como saída e força o LED a desligar logo na inicialização
  pinMode(pinoLed, OUTPUT);
  digitalWrite(pinoLed, LOW); 

  // Inicia a conexão Wi-Fi
  Serial.println();
  Serial.print("Conectando-se à rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado com sucesso!");
  Serial.print("Abra o navegador e digite o IP: http://");
  Serial.println(WiFi.localIP());

  // Inicia o servidor web
  server.begin();
}

void loop() {
  // Ouve por clientes (navegadores) tentando acessar o IP do ESP32
  WiFiClient client = server.available();   

  if (client) {
    String currentLine = "";                
    
    while (client.connected()) {
      if (client.available()) {             
        char c = client.read();             
        
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            
            // --- MONTAGEM DA PÁGINA WEB (HTML) ---
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>ESP32 Web Server</title>");
            client.println("<style>");
            client.println("body { font-family: Arial; text-align: center; margin: 0px; padding-top: 50px; background-color: #f4f4f9; }");
            client.println("h1 { color: #333; }");
            client.println(".btn { background-color: #4CAF50; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 20px; margin: 10px 2px; cursor: pointer; border-radius: 8px; border: none; }");
            client.println(".btn-off { background-color: #f44336; }");
            client.println("p { font-size: 18px; color: #666; }");
            client.println("</style></head>");
            
            client.println("<body>");
            client.println("<h1>Controle do LED ESP32</h1>");
            
            // Mostra o estado atual na tela
            client.println("<p>Estado atual: <strong>" + estadoLed + "</strong></p>");
            
            // Cria os botões dependendo do estado real
            if (estadoLed == "DESLIGADO") {
              client.println("<p><a href=\"/LED=ON\"><button class=\"btn\">LIGAR LED</button></a></p>");
            } else {
              client.println("<p><a href=\"/LED=OFF\"><button class=\"btn btn-off\">DESLIGAR LED</button></a></p>");
            }
            
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Verifica o comando enviado pelo navegador
        if (currentLine.endsWith("GET /LED=ON")) {
          digitalWrite(pinoLed, LOW);
          estadoLed = "LIGADO";
        }
        if (currentLine.endsWith("GET /LED=OFF")) {
          digitalWrite(pinoLed, HIGH);
          estadoLed = "DESLIGADO";
        }
      }
    }
    client.stop();
  }
}