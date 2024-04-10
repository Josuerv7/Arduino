// This example sends data to multiple variables to
// Ubidots through HTTP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-9o2y9x0l3ZbfHwru5YzCsuddx22XGj";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "ThinkPad-E495";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "12345678";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

#include "DHT.h"

#define DHTPIN 2   // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define led1 16
#define led2 5
#define led3 4

DHT dht(2, DHT11);
  //Pin digital 3 para el echo del sensor

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
 
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);



 Serial.println(F("DHTxx test!"));

  dht.begin();

   
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}


void loop() {   

int valorsensor= analogRead (A0);

float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));


  if (t> 33){
digitalWrite(led2,HIGH);
delay(300);
digitalWrite(led2,LOW);
delay(300);
digitalWrite(led2,HIGH);
delay(300);
digitalWrite(led2,LOW);
delay(300);
  }else{
    digitalWrite(led2,LOW);
  }

  if (h> 56){
digitalWrite(led1,HIGH);
delay(300);
digitalWrite(led1,LOW);
delay(300);
digitalWrite(led1,HIGH);
delay(300);
digitalWrite(led1,LOW);
delay(300);
  }else{
    digitalWrite(led1,LOW);
  }

  if (valorsensor> 800){
digitalWrite(led3,HIGH);
delay(300);
digitalWrite(led3,LOW);
delay(300);
digitalWrite(led3,HIGH);
delay(300);
digitalWrite(led3,LOW);
delay(300);

  }else{
    digitalWrite(led3,LOW);
  }





ubidots.add("Temperatura", t);
ubidots.add("Humedad", h);
ubidots.add("Luz", valorsensor);


 bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }
  
}


