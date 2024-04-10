unsigned long previousMillis = 0;
const long interval = 1000; // Intervalo de 1 segundo (1000 milisegundos)
int currentTask = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    if (currentTask == 1) {
      Serial.println("Tarea 1");
    } else if (currentTask == 2) {
      Serial.println("Tarea 2");
    } else if (currentTask == 3) {
      Serial.println("Tarea 3");
    }

    currentTask = (currentTask % 3) + 1; // Cambia a la siguiente tarea (1, 2 o 3)
    previousMillis = currentMillis;
  }
 
}
