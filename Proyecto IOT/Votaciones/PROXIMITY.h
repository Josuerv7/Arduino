#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <Arduino.h>

// Declaración de pines
const int TRIGGER_PIN = 2;  
const int ECHO_PIN = 0;
const int LED_PIN = 27;  

// Clase Proximity
class Proximity {
  public:
    // Constructor
    Proximity();
    
    // Métodos
    void init();
    void read();
    
  private:
    long duration;
    int distance;   
};

// Constructor
Proximity::Proximity() {

}

// Inicialización de pines
void Proximity::init() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);  
}

// Lectura del sensor y encendido de LED
void Proximity::read() {

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2; // Fórmula para cm
  
  if(distance < 10){ 
    digitalWrite(LED_PIN, HIGH);
  } else {
     digitalWrite(LED_PIN, LOW);   
  }
}

#endif //PROXIMITY_H