#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledRojo = 6; // Está Seco
int ledAmarillo = 5; // Menos Seco
int ledBlanco = 4; // Un Poco Humedo
int ledAzul = 3; // Más Humedo
int ledVerde = 2; // En Agua
int SensorPin = A0; // Pin Análogo

// Valores del Sensor
int valorMinimoSensor = 0;
int valorMaximoSensor = 1023;
int valorMinimoMapeado = 100;
int valorMaximoMapeado = 0;

// Caracter Personalizado (Gota de Agua)
byte waterDrop[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

void setup() {
  Serial.begin(9600);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledBlanco, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, waterDrop);
}

// Esta funcion muestra la humedad en la pantalla LCD
void mostrarHumedadLCD(int valor) {
  lcd.setCursor(0, 0);
  lcd.print("La humedad es:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  lcd.print("%");
  lcd.setCursor(4, 1);
  lcd.write(waterDrop);
}

// 
void mostrarHumedadSerial(int valor) {
  Serial.print("La humedad es: ");
  Serial.print(valor);
  Serial.println("%");
}

void controlarLEDS(int humedad) {
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledBlanco, LOW);
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);

  // Encender el LED correspondiente al nivel de humedad
  if (humedad >= 1000) {
    Serial.println(">>El sensor está desconectado o está seco");
    digitalWrite(ledRojo, HIGH); // Enciende el LED rojo
  } else if (humedad < 1000 && humedad >= 800) {
    Serial.println(">>El suelo está menos seco");
    digitalWrite(ledAmarillo, HIGH); // Enciende el LED amarillo
  } else if (humedad < 800 && humedad >= 600) {
    Serial.println(">>El suelo está un poco húmedo");
    digitalWrite(ledBlanco, HIGH); // Enciende el LED blanco
  } else if (humedad < 600 && humedad >= 400) {
    Serial.println(">>El suelo está húmedo");
    digitalWrite(ledAzul, HIGH); // Enciende el LED azul
  } else if (humedad < 400) {
    Serial.println(">>El sensor está en agua");
    digitalWrite(ledVerde, HIGH); // Enciende el LED verde
  }
}

void loop() {
  int humedad = analogRead(SensorPin); // Leer el valor de humedad del pin A0 de Arduino
  int valorMapeado = map(humedad, valorMinimoSensor, valorMaximoSensor, valorMinimoMapeado, valorMaximoMapeado); // Mapea el valor de humedad a un porcentaje
  
  Serial.print("Valor mapeado: ");
  Serial.println(valorMapeado);

  mostrarHumedadSerial(valorMapeado);
  mostrarHumedadLCD(valorMapeado);
  controlarLEDS(humedad);
  delay(1000);
}