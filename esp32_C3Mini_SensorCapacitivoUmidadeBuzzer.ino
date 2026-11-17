const int umidadeAnalogPin = 0; // Conecte o AO do sensor no GPIO 0 (A0)
const int buzzerPin = 5;        // Buzzer no GPIO 5

// Defina um limiar (threshold) com base nos testes no seu ambiente.
// Valores abaixo deste limiar indicarão presença de umidade/água.
const int valorReferencia = 2200; 

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  int valorLido = analogRead(umidadeAnalogPin); // No ESP32-C3, lê de 0 a 4095

  Serial.print("Valor lido (Capacitivo): ");
  Serial.println(valorLido);

  // Se o valor cair abaixo do limiar, significa que detectou umidade/água
  if (valorLido < valorReferencia) {
    Serial.println("-> Umidade/Água detectada! Tocando buzzer.");
    digitalWrite(buzzerPin, HIGH);
  } else {
    Serial.println("-> Seco.");
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);
}