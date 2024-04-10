#include "DHT.h"
#include <Servo.h>
#include <ESP8266WiFi.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(2, DHT11);

Servo myservo;
#define servoPin  16 // El servo en el D3
int grado = 180;

const char* ssid = "ThinkPad-E495";
const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  dht.begin();

  WiFi.begin(ssid, password);
  myservo.attach(servoPin);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado con WiFi.");

  server.begin();
  Serial.println("Servidor web iniciado.");

  Serial.print("Esta es la IP para conectar: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: ")); 
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println("°C");

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.print("Nuevo cliente: ");
  Serial.println(client.remoteIP());

  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);

  if (req.indexOf("calcular") != -1) {
     Serial.print(F("Humidity: ")); 
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println("°C");
  }
  if (req.indexOf("dispensar") != -1) {
    grado = grado - 180;
    myservo.write(grado);
    delay(200);
    grado = grado + 180;
    myservo.write(grado);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta charset=utf-8></head>");
  client.println("<body><center><font face='Arial'>");
  client.println("<h2><font color='#009900'>DISPENSAPET</font></h2>");
  client.println("<br><br>");
  client.println("<a href='dispensar'><button>Pulsa para dispensar</button></a>");
  client.println("<br>");

  client.print("<h3>Temperatura: ");
  client.print(t);
  client.println("°C</h3>");

client.println("<a href='calcular'><button>Calcular</button></a>");


  client.println("</font></center></body></html>");

  Serial.print("Cliente desconectado: ");
  Serial.println(client.remoteIP());
}
