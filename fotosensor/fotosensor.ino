void setup() {
Serial.begin(115200);
 pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
int valorsensor= analogRead (A0);
delay(500);

if(valorsensor >= 80){
  Serial.println("Apagado");
  Serial.println(valorsensor);
  digitalWrite(LED_BUILTIN, HIGH);
}else{ 
Serial.println("Encendido");
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(valorsensor);
}
}