// Definición de pines
const int relayPin = 7;  // Pin digital conectado al relé

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Activa el relé para encender el LED
  digitalWrite(relayPin, HIGH); // Activa el relé
  delay(1000);                 // Espera 2 segundos

  // Desactiva el relé para apagar el LED
  digitalWrite(relayPin, LOW);  // Desactiva el relé
  delay(1000);                 // Espera 2 segundos
}
