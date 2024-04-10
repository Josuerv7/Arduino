void setup() {
Serial.begin(115200);
}

void loop() {
int valorsensor= analogRead (A0);
int valorpotenciometro= analogRead (A1);
delay(500);
Serial.print("LDR: ");
Serial.println(valorsensor);
Serial.print("ADC: ");
Serial.println(valorpotenciometro);
}
