#define D0 16
#define D1 05
#define D2 04
#define D3 00
#define D4 02
#define D5 14
#define D6 12
#define D7 13

const int ledPins[] = {16, 05, 04, 00, 02, 14, 12, 13};

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void loop() {
  for (int count = 0; count <= 255; count++) {
    for (int i = 0; i < 8; i++) {
      if (bitRead(count, i)) { // bit read sirve para ir recorriento en funcion de los bits, para ello el ciclo que va aumentando conforme se cuentan los valores del los leds.
        digitalWrite(ledPins[i], HIGH); 
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
    delay(500);
  }
}
