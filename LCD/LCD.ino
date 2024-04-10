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
int valorMaximoSensor = 102;
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


  if (humedad >= 1000) {
    Serial.println("Esta seco");
    digitalWrite(ledRojo, HIGH); 
  } else if (humedad < 1000 && humedad >= 800) {
    Serial.println("Poco humedo");
    digitalWrite(ledAmarillo, HIGH); 
  } else if (humedad < 800 && humedad >= 600) {
    Serial.println("Poco humedo");
    digitalWrite(ledBlanco, HIGH); 
  } else if (humedad < 600 && humedad >= 400) {
    Serial.println("Está húmedo");
    digitalWrite(ledAzul, HIGH); 
  } else if (humedad < 400) {
    Serial.println("Muy humedo");
    digitalWrite(ledVerde, HIGH); 
  }
}

void loop() {
  int humedad = analogRead(SensorPin); 
  int valorMapeado = map(humedad, valorMinimoSensor, valorMaximoSensor, valorMinimoMapeado, valorMaximoMapeado); // Mapea el valor de humedad a un porcentaje
  
  Serial.print("Valor mapeado: ");
  Serial.println(humedad);

  mostrarHumedadSerial(valorMapeado);
  mostrarHumedadLCD(valorMapeado);
  controlarLEDS(humedad);
  delay(1000);
}