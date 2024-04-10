#include "DHT.h"
#include <Servo.h>
#include <ESP8266WiFi.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(2, DHT11);

Servo myservo;
#define servoPin  16 // El servo en el D3
int grado = 0;

const int Trigger = 5;   //Pin digital 2 para el Trigger del sensor
const int Echo = 4;

const char* ssid = "ThinkPad-E495";
const char* password = "12345678";

WiFiServer server(80);

unsigned long lastRefreshTime = 0;
const unsigned long refreshInterval = 5000; // Intervalo de refresco en milisegundos

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  
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

////////////////////////////SENSOR DE PROXIMDA
long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100); 
 ///////////////////////////////////////////Sensor de temperatura///////////////
  float h = dht.readHumidity();
  float tmp = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: ")); 
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(tmp);
  Serial.println("°C");


  if (req.indexOf("dispensar50") != -1) {
    grado = grado + 180;
    myservo.write(grado);
    delay(100);
    grado = grado - 180;
    myservo.write(grado);
  }

  if (req.indexOf("dispensar100") != -1) {
    grado = grado + 180;
    myservo.write(grado);
    delay(180);
    grado = grado - 180;
    myservo.write(grado);
  }

  if (req.indexOf("dispensar120") != -1) {
    grado = grado + 180;
    myservo.write(grado);
    delay(210);
    grado = grado - 180;
    myservo.write(grado);
  }

  unsigned long currentTime = millis();
  if (currentTime - lastRefreshTime >= refreshInterval) {
    sendWebPage(client, tmp, d); // Enviar la página web al cliente
    lastRefreshTime = currentTime; // Actualizar el tiempo de último refresco
  }
}

void sendWebPage(WiFiClient client, float temperature, long distance) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE html>");
  client.println("<html lang=\"en\">");
  client.println("<head>");
  client.println("    <meta charset=\"UTF-8\">");
  client.println("    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
  client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("    <title>Dispensador</title>");
  client.println("    <style>");
  client.println("        body {");
  client.println("            font-family: Arial, sans-serif;");
  client.println("            margin: 0;");
  client.println("            padding: 20px;");
  client.println("            text-align: center;");
  client.println("            background-image: url(\"https://cdn.onemars.net/sites/nutro_es_NkyIN_B9cV/image/gettyimages-1140006304_1615921633324.jpeg\");");
  client.println("            background-size: cover;");
  client.println("            background-position: center;");
  client.println("        }");
  client.println("        h1 {");
  client.println("            color: #333;");
  client.println("            font-size: 48px;");
  client.println("            margin-bottom: 40px;");
  client.println("        }");
  client.println("        .section {");
  client.println("            margin-bottom: 60px;");
  client.println("        }");
  client.println("        .section h2 {");
  client.println("            font-size: 32px;");
  client.println("            margin-bottom: 20px;");
  client.println("        }");
  client.println("        .section p {");
  client.println("            color: #666;");
  client.println("            font-size: 24px;");
  client.println("        }");
  client.println("        .btn {");
  client.println("            background-color: #4CAF50;");
  client.println("            border: none;");
  client.println("            color: white;");
  client.println("            padding: 16px 32px;");
  client.println("            text-align: center;");
  client.println("            text-decoration: none;");
  client.println("            display: inline-block;");
  client.println("            font-size: 28px;");
  client.println("            margin: 10px;");
  client.println("            cursor: pointer;");
  client.println("            border-radius: 8px;");
  client.println("            transition: background-color 0.3s ease;");
  client.println("        }");
  client.println("        .btn:hover {");
  client.println("            background-color: #45a049;");
  client.println("        }");
  client.println("    </style>");
  client.println("</head>");
  client.println("<body>");
  client.println("    <h1>Tu dispensador de croquetas</h1>");
  client.println("    <div class=\"section\">");
  client.println("        <h2>¿Deseas darle de comer a tu mascota?</h2>");
  client.println("        <button type=\"button\" class=\"btn\" onclick=\"performAction('dispensar120');\">120 gramos</button>");
  client.println("        <button type=\"button\" class=\"btn\" onclick=\"performAction('dispensar100');\">100 gramos</button>");
  client.println("        <button type=\"button\" class=\"btn\" onclick=\"performAction('dispensar50');\">50 gramos</button>");
  client.println("    </div>");
  client.println("        <h2>Temperatura del área del comedero</h2>");
  client.println("        <label id=\"temperatureLabel\" style=\"color: white; font-size: 24px; background-color: black; border-radius: 8px;\">");
  client.println(temperature);
  client.println("        </label>");
  client.println("    </div>");
  client.println("    <div class=\"section\">");
  client.println("        <h2>Distancia al comedero</h2>");
  client.println("        <label id=\"distanceLabel\" style=\"color: white; font-size: 24px; background-color: black; border-radius: 8px;\">");
  client.println(distance);
  client.println("        </label>");
  client.println("    </div>");

if (distance < 30) {
    client.println("        <label id=\"alertLabel\" style=\"color: red; font-size: 24px;\">");
    client.println("            Tu perro está cerca");
    client.println("        </label>");
} else {
    client.println("        <label id=\"alertLabel\" style=\"color: green; font-size: 24px;\">");
    client.println("            Sin alerta");
    client.println("        </label>");
}

  client.println("    <script>");
  client.println("        setTimeout(function() {");
  client.println("            location.reload();");
  client.println("        }, 5000);"); // Refrescar la página cada 5 segundos (5000 milisegundos)
  client.println("");
  client.println("        function performAction(action) {");
  client.println("            var xhttp = new XMLHttpRequest();");
  client.println("            xhttp.open('GET', '/' + action, true);");
  client.println("            xhttp.send();");
  client.println("        }");
  client.println("    </script>");
  client.println("</body>");
  client.println("</html>");

}
