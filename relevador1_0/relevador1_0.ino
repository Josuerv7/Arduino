const int relayPin = 7;  // Pin digital conectado al relé

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(115200);  // Inicializa la comunicación serial a 9600 baudios
}

void loop() {
  if (Serial.available() > 0) {
    int value = Serial.parseInt(); // Lee un valor numérico desde la consola serial
    if (value == 0) {
      digitalWrite(relayPin, HIGH); // Activa el relé
      Serial.println("Relé desactivado");
    } else if (value == 1) {
      digitalWrite(relayPin, LOW); // Desactiva el relé
      Serial.println("Relé activado");
    }
    
    // Espera hasta que no haya más datos en el búfer de entrada
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
