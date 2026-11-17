const int sensorChuvaPino = 0; // Conecte o AO do sensor no GPIO 0 (A0)
const int buzzerPino = 5;     // Buzzer no GPIO 5
const int valorReferencia = 4000; 

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPino, OUTPUT);
  digitalWrite(buzzerPino, LOW);
}

void loop() {
  int valorLido = analogRead(sensorChuvaPino); // No ESP32-C3, lê de 0 a 4095
  
  Serial.print("Valor lido (AO): ");
  Serial.println(valorLido);

  if (valorLido < valorReferencia) {
    Serial.println("-> Chuva detectada! Tocando buzzer.");
    digitalWrite(buzzerPino, HIGH);
  } else {
    Serial.println("-> Tempo seco.");
    digitalWrite(buzzerPino, LOW);
  }

  delay(500);
}