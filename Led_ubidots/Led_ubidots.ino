// This example retrieves last value of a variable from the Ubidots API
// using HTTP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-9o2y9x0l3ZbfHwru5YzCsuddx22XGj";                                     // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Galaxy A52";                                         // Put here your Wi-Fi SSID
const char* WIFI_PASS = "vjbe7060";                                         // Put here your Wi-Fi password
const char* DEVICE_LABEL_TO_RETRIEVE_VALUES_FROM = "2c3ae838b758";  // Replace with your device label
const char* VARIABLE_LABEL_TO_RETRIEVE_VALUES_FROM = "Rosas";       // Replace with your variable label

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

// This example retrieves last value of a variable from the Ubidots API
// using HTTP protocol.

/**************
 * Include Libraries
 **************/



/**************
 * Auxiliar Functions
 **************/

// Put here your auxiliar functions

/**************
 * Main Functions
 **************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true); //Uncomment this line for printing debug messages
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  ubidots.add("Rosas", LED_BUILTIN);
   bool bufferSent = false;
  bufferSent = ubidots.send();
  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }   


  /* Obtain last value from a variable as float using HTTP */
  float value = ubidots.get(DEVICE_LABEL_TO_RETRIEVE_VALUES_FROM, VARIABLE_LABEL_TO_RETRIEVE_VALUES_FROM);
  if (value != ERROR_VALUE) {
    Serial.print("Value:");
    Serial.println(value);
    digitalWrite(LED_BUILTIN, value);
  }
 
  // Evaluates the results obtained
  delay(1000);
}


