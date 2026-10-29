// Definição do pino GPIO do ESP32 conectado ao pino S (Sinal) do KY-031
const int PIN_SENSOR_IMPACTO = 4;  // Mantenha o GPIO que você usou (ex: 16)

// Pino do LED embutido na maioria das placas ESP32 (LED_BUILTIN é geralmente 2)
const int PIN_LED_EMBUTIDO = 2; 

// Variável para armazenar o estado atual do sensor
int estado_sensor = 0; 

void setup() {
  // Inicializa a comunicação Serial
  Serial.begin(115200); 
  Serial.println("Inicializando Sensor de Impacto KY-031 com LED de Alerta...");

  // Configura o pino do sensor como entrada
  pinMode(PIN_SENSOR_IMPACTO, INPUT); 

  // Configura o pino do LED embutido como saída
  pinMode(PIN_LED_EMBUTIDO, OUTPUT);
  
  // Garante que o LED comece desligado
  digitalWrite(PIN_LED_EMBUTIDO, LOW);
}

void loop() {
  // Lê o estado do pino do sensor
  estado_sensor = digitalRead(PIN_SENSOR_IMPACTO);

  /* Lógica: LOW (0) quando há impacto/vibração. */

  if (estado_sensor == LOW) {
    // 1. Acende o LED
    digitalWrite(PIN_LED_EMBUTIDO, HIGH);

    // 2. Mostra a mensagem no Monitor Serial
    Serial.println("==================================");
    Serial.println("  >>> IMPACTO DETECTADO! (LED ACESO) <<<");
    Serial.println("==================================");
    
    // Pequeno atraso para "debounce" (evitar múltiplas detecções rápidas)
    delay(600); 

    // Opcional: Loop para esperar o sinal voltar ao normal (HIGH) antes de procurar um novo impacto
    while (digitalRead(PIN_SENSOR_IMPACTO) == LOW) {
      delay(10); 
    }
    
    // 3. Desliga o LED após o ciclo de detecção/debounce
    digitalWrite(PIN_LED_EMBUTIDO, LOW);
  }

  // Pequeno atraso para evitar leituras muito rápidas quando não há impacto
  delay(10); 
}