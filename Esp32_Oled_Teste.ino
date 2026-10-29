#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configurações do Display OLED
#define LARGURA_TELA 128 // Largura do display em pixels
#define ALTURA_TELA  64  // Altura do display em pixels

// Pinos I2C internos da placa HW-724
#define OLED_SDA 5
#define OLED_SCL 4

// O pino de Reset não é utilizado na maioria dessas placas (-1)
#define OLED_RESET -1 
// Endereço I2C padrão do display (geralmente 0x3C)
#define ENDERECO_DISPLAY 0x3C 

// Cria o objeto para controle do display
Adafruit_SSD1306 display(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);

int contador = 0;

void setup() {
  // Inicializa o canal serial para debug
  Serial.begin(115200);
  Serial.println("Inicializando o teste do HW-724...");

  // Inicializa a comunicação I2C definindo os pinos corretos do HW-724
  Wire.begin(OLED_SDA, OLED_SCL);

  // Inicializa o display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, ENDERECO_DISPLAY)) {
    Serial.println(F("Falha ao inicializar o display SSD1306. Verifique os pinos!"));
    // Se falhar, tenta a configuração alternativa (algumas placas usam SDA=21 e SCL=22)
    // Descomente a linha abaixo se a tela continuar apagada:
    // Wire.begin(21, 22);
    for(;;); // Trava o código aqui se o display não responder
  }

  // Limpa o buffer interno do display
  display.clearDisplay();

  // Exibe uma mensagem de boas-vindas inicial
  display.setTextSize(1);             // Tamanho do texto (1 é o padrão)
  display.setTextColor(SSD1306_WHITE); // Cor do texto
  display.setCursor(0, 0);            // Posição x, y (superior esquerdo)
  display.println("ESP32 HW-724");
  display.println("Display OK!");
  display.display();                  // Envia os comandos para a tela
  delay(2000);
}

void loop() {
  // Limpa a tela a cada ciclo para não sobrepor o texto anterior
  display.clearDisplay();

  // Desenha uma borda simples na tela
  display.drawRect(0, 0, LARGURA_TELA, ALTURA_TELA, SSD1306_WHITE);

  // Título do teste
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.println("TESTE DE CODIGO");

  // Exibe o contador incrementando
  display.setTextSize(2); // Texto maior para o número
  display.setCursor(20, 30);
  display.print("Cont: ");
  display.print(contador);

  // Renderiza tudo na tela física
  display.display();

  // Incrementa a variável e exibe no monitor serial
  Serial.print("Contagem: ");
  Serial.println(contador);
  contador++;

  delay(1000); // Aguarda 1 segundo antes de repetir
}
