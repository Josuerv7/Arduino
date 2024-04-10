#ifndef Actuadores_h
#define Actuadores_h
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27,16,2);

class actuadores{
  public:
  void lcd_init (void);
  void imprimir (String, bool);

};

void actuadores :: lcd_init(void){
lcd.init();
lcd.backlight();
}

void actuadores :: imprimir(String msg, bool fila){
  lcd.setCursor(0,fila);
  lcd.print(msg);
  lcd.print("                ");
}
#endif