#include <LiquidCrystal_I2C.h>

#define BUZZER_PIN 6
#define RIGHT_BUTTON_PIN 9
#define LEFT_BUTTON_PIN 10
#define DOWN_BUTTON_PIN 11
#define UP_BUTTON_PIN 12

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte caracter1 [ ] = {
  B01010,
  B11111,
  B10101,
  B10001,
  B11011,
  B10001,
  B01010,
  B00100							/*~ ⬛⬜⬜⬜⬛~*/
};

/*~ Icono o caracter 2 ~*/
byte caracter2 [ ] = {
   B00100,
  B00100,
  B01110,
  B11011,
  B01010,
  B01010,
  B01010,
  B00100							/*~ ⬛⬛⬜⬛⬛~*/
};

byte caracter3 [ ] = {
   B01110,
  B11011,
  B10101,
  B11011,
  B01110,
  B00100,
  B01100,
  B00100							/*~ ⬛⬛⬜⬛⬛~*/
};


bool leftButtonState = false,
     downButtonState = false,
     upButtonState = false,
     rightButtonState = false;

char menu[3][4][30] = {
    {"a. Paramecia", "i. Gomu Gomu No Mi", "ii. Ope Ope No Mi", "iii. Gura Gura No Mi"},
    {"b. Zoan", "i. Hito Hito No Mi", "ii. Ushi Ushi No Mi", "iii. Uo Uo No Mi"},
    {"c. Logia", "i. Mera Mera No Mi", "ii. Yami Yami No Mi", "iii. Moku Moku No Mi"}
};

int currentCategory = 0;
int currentElement = 0;

// Button debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;

void showCategory() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(menu[currentCategory][0]);
    lcd.setCursor(0, 1);
    lcd.print(menu[currentCategory][currentElement]);
}

// Function to generate a tone, pass the frequency as an integer
void playTone(int frequency) {
    tone(BUZZER_PIN, frequency);
    delay(20);
    noTone(BUZZER_PIN);
}

void setup() {
    lcd.init();
    lcd.backlight();
  
  lcd.createChar ( 0, caracter1 );   	/*~ Indicar al programa que genere un caracter a partir del array de bits. ~*/
  lcd.createChar ( 1, caracter2 );  
  lcd.createChar ( 2, caracter3 );
  
  lcd.setCursor ( 0, 0 );   	/*~ ( columnas, filas) Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0) ~*/
   lcd.write ( 0 );		  		/*~ Mostramos nuestro primer icono o caracter ~*/
   	delay ( 1000 );	
  /*~ Esperar 1 segundo ~*/
   lcd.clear ( );				/*~ Limpiar pantalla ~*/
   lcd.setCursor ( 0, 1 );   	/*~ ( columnas, filas) Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1) ~*/
   lcd.write ( 1 );          	/*~ Mostramos nuestro segundo icono o caracter ~*/
    delay ( 1000 );				/*~ Esperar 1 segundo ~*/
   lcd.clear ( );
  
  lcd.setCursor ( 0, 0 );   	/*~ ( columnas, filas) Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1) ~*/
   lcd.write ( 2 );          	/*~ Mostramos nuestro segundo icono o caracter ~*/
    delay ( 1000 );				/*~ Esperar 1 segundo ~*/
   lcd.clear ( );
  
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
    pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

    showCategory();
}

void loop() {
  
  	
  
    leftButtonState = digitalRead(LEFT_BUTTON_PIN);
    downButtonState = digitalRead(DOWN_BUTTON_PIN);
    upButtonState = digitalRead(UP_BUTTON_PIN);
    rightButtonState = digitalRead(RIGHT_BUTTON_PIN);

    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime > debounceDelay) {
        if (!downButtonState) {
            currentCategory++;
            playTone(600);
            if (currentCategory >= 3) {
                currentCategory = 0;
            }
            currentElement = 0;
            showCategory();
            delay(250);
        }

        if (!upButtonState) {
            currentCategory--;
            playTone(900);
            if (currentCategory < 0) {
                currentCategory = 2;
            }
            currentElement = 0;
            showCategory();
            delay(250);
        }

        if (!rightButtonState) {
            if (currentElement < 3) {
                currentElement++;
                playTone(2700);
            }
            showCategory();
        }

        if (!leftButtonState) {
            if (currentElement > 0) {
                currentElement--;
                playTone(3000);
            }
            showCategory();
        }
    }
}
