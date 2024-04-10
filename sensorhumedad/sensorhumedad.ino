#include <LiquidCrystal_I2C.h>




LiquidCrystal_I2C lcd(32, 16, 2); // Pines de conexión al LCD (ajusta según tu configuración)
int moisture = 0;

void setup()
{
  Serial.begin(115200);
  
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  lcd.init();
  lcd.backlight(); // Inicializa el LCD con 16 columnas y 2 filas
  lcd.print("Humedad: ");
}

void loop()
{
  digitalWrite(A0, HIGH);
  delay(10);
  moisture = analogRead(A1);
  digitalWrite(A0, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  
  // Ajusta la escala para que 1023 represente el 100%
  int percentage = map(moisture, 0, 1023, 0, 100);
  
  lcd.setCursor(9, 0);
  lcd.print("      ");
  lcd.setCursor(9, 0);
  lcd.print(percentage);
  lcd.print("%");
  Serial.println(moisture);
  if (moisture < 200) {
    digitalWrite(2, HIGH);
  } else if (moisture < 400) {
    digitalWrite(3, HIGH);
  } else if (moisture < 600) {
    digitalWrite(4, HIGH);
  } else if (moisture < 800) {
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(6, HIGH);
  }
  
  delay(100);
}
