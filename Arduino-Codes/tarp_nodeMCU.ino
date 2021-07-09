#include <DHT.h>
#include <ESP8266WiFi.h>

//String apiKey = "I5PWJI9P4M9IDKBV";     //  ThingSpeak API key
String apiKey = "8V4297HO8FD7M4JZ";

const char *ssid =  "MMULASI";     // WiFI ssid
const char *pass =  "atlas1234";
const char* server = "api.thingspeak.com";

#define DHTPIN 0
#define moisture_pin 2

DHT dht(DHTPIN, DHT22);

WiFiClient client;

void setup()
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid); 

       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED)
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}

void loop() 
{  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      int moisture = analogRead(moisture_pin);
      int m = 100 - (moisture*100/1023);
      
                      if (client.connect(server,80))
                      {                          
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(m);
                             postStr +="&field2=";
                             postStr += String(t);
                             postStr +="&field3=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.print("%. Soil Moisture: ");
                             Serial.print(m);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
          Serial.println("Waiting...");
          
  delay(10000);
}
