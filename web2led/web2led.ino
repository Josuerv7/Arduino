/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/
#define D0 16
bool blink=false;
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Galaxy A52"
#define STAPSK "vjbe7060"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  pinMode(D0, OUTPUT);
  digitalWrite(D0, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
if (blink==true ){
      digitalWrite(D0, LOW);  
     delay(400);                      
     digitalWrite(D0, HIGH); 
     delay(400);}   
  WiFiClient client = server.accept();
  if (!client) { return; }
  Serial.println(F("new client"));
  client.setTimeout(5000);  // default is 1000
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    val = 1;
   }
  else{
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }
digitalWrite(LED_BUILTIN, val);

  int val2;
  if (req.indexOf(F("/gpio/3")) != -1) {
    val2 = 0;
  } else if (req.indexOf(F("/gpio/2")) != -1) {
    val2 = 1; 
    } else if (req.indexOf(F("/gpio/4")) != -1) {
   blink=true;
  }else if (req.indexOf(F("/gpio/5")) != -1) {
   blink=false;
   digitalWrite(val2, HIGH);
  } else {
    Serial.println(F("invalid request"));
    val2 = digitalRead(D0);
  }
digitalWrite(D0, val2);

// read/ignore the rest of the request
// do not client.flush(): it is for output only, see below
while (client.available()) {
  // byte by byte is not very efficient
  client.read();
}
  
// Send the response to the client
// it is OK for multiple small client.print/write,
// because nagle algorithm will group them into one single packet
client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html><center>\r\nLed Interno esta "));
client.print((val) ? F("Apagado") : F("Encendido"));
client.print(F("<br>Click <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio/1'>aqui</a> para apagar el LED Interno, o <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio/0'>aqui</a> para encender el LED Interno</html><br><br>"));

client.print(F("Led Externo esta "));
client.print((val2) ? F("Encendido") : F("Apagado"));
client.print(F("<br>Click <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio/3'>aqui</a> para apagar el LED Interno, o <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio/2'>aqui</a> para encender el LED Externo</html><br><br>"));

client.print(F("Led Externo "));
client.print((blink) ? F("esta Parpadeando") : F("no esta Parpadeando"));
client.print(F("<br>Click <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio/4'>aqui</a> para parpadear o <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio/5'>aqui</a> para dejar de parpadear </html><br><br>"));
// The client will actually be *flushed* then disconnected
// when the function returns and 'client' object is destroyed (out-of-scope)
// flush = ensure written data are received by the other side
Serial.println(F("Disconnecting from client"));
}
