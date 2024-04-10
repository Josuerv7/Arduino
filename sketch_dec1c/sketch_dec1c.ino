

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial
  delay(1000);
  
  // Conexión a la red WiFi

  Serial.println("Conectado a la red WiFi");
}

void loop() {
  Serial.println("¡Hola, mundo!");
  delay(1000);
}