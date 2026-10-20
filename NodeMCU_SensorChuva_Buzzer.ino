// Definição dos pinos no NodeMCU V3
const int PIN_SENSOR = D1; // Pino onde o DO do sensor está ligado
const int PIN_BUZZER = D2; // Pino onde o sinal do Buzzer está ligado
const int LED_PLACA  = D4; // LED integrado para ajuda visual

void setup() {
  Serial.begin(115200);
  
  // Configuração dos pinos
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(LED_PLACA, OUTPUT);
  
  // Garante que o buzzer comece desligado
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(LED_PLACA, HIGH); // Apaga LED integrado (lógica invertida)

  Serial.println("--- Sistema de Alarme de Chuva Inicializado ---");
}

void loop() {
  // Lê o estado do sensor de chuva (LOW = Molhado, HIGH = Seco)
  int statusChuva = digitalRead(PIN_SENSOR);

  if (statusChuva == LOW) {
    // CHOVENDO!
    Serial.println("AGUA DETECTADA! Acionando alarme...");
    
    digitalWrite(LED_PLACA, LOW);  // Acende o LED da placa
    digitalWrite(PIN_BUZZER, HIGH); // Liga o Buzzer
    delay(50);                    // Efeito de bip rápido
  } else {
    // SECO
    Serial.println("FORA DA AGUA! Alarme desligado.");
    digitalWrite(PIN_BUZZER, LOW); // Garante buzzer desligado
    digitalWrite(LED_PLACA, HIGH);  // Apaga o LED da placa
    delay(50);                   // Monitora a cada 1 segundo
  }
}
