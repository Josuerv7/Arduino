// 5E, 16/08/23, Rosas Vazquez Eduardo Josue 

void setup() {
  //Se establece la frecuencia de muestreo de la consola
  Serial.begin(9600);
}

void loop() {
  // Se introuce dentro del loop el mensaje a mostrar, utilizando el comando Serial.println, este realiza un salto de linea cada que imprime algo.
Serial.println("hola mundo");
//El delay retrasa cualquier instruccion dentro del loop en milisegundos.
delay(1000);
}
