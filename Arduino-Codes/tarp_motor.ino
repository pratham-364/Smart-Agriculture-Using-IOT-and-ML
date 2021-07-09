#include <DHT.h>
#include<LiquidCrystal.h>

#define moisture_sensorPin A0
#define DHTPIN 7
#define motorPin 4
#define soil_statusPin 2        //LED soil moisture status
LiquidCrystal lcd(13,12,11,10,9,8);
DHT dht(DHTPIN, DHT22);
const int avg_moisture = 600; 

void setup()
{
Serial.begin(9600);
lcd.begin(16,2);
lcd.clear(); 
lcd.setCursor(0,0);
lcd.print(" AUTOMATIC ");
lcd.setCursor(0,1);
lcd.print(" IRRIGATION S/M ");
dht.begin();
delay(10000);

pinMode(moisture_sensorPin,INPUT);
pinMode(motorPin,OUTPUT);
pinMode(soil_statusPin,OUTPUT);

digitalWrite(motorPin,LOW);
digitalWrite(soil_statusPin,LOW);
}

void loop()
{
float h;
float t;
int moisture;
float moisture_ft;
float m;

lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print(" MOISTURE - ");
moisture = analogRead(moisture_sensorPin);
moisture_ft = analogRead(moisture_sensorPin);
m = 100 - (100*moisture_ft/1023);
lcd.print(moisture);
lcd.setCursor(0,1);
lcd.print(m);
lcd.print(" %");
delay(7000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperature - ");
t = dht.readTemperature();
lcd.print(t);
lcd.setCursor(0,1);
lcd.print("Humidity - ");
h = dht.readHumidity();
lcd.print(h);
delay(5000);
lcd.clear();

digitalWrite(motorPin,LOW);
if(analogRead(moisture_sensorPin) > avg_moisture)
{ 
while(analogRead(moisture_sensorPin) > avg_moisture)
{
lcd.setCursor(0,0);
lcd.print(" MOISTURE - LOW");
lcd.setCursor(0,1);
lcd.print(" MOTOR - ON ");
digitalWrite(soil_statusPin,LOW); 
digitalWrite(motorPin,HIGH);
}}

if(analogRead(moisture_sensorPin) < avg_moisture)
{
lcd.setCursor(0,0);
lcd.print(" MOISTURE - HIGH");
lcd.setCursor(0,1);
lcd.print(" MOTOR - OFF "); 
digitalWrite(soil_statusPin,HIGH);
digitalWrite(motorPin,LOW);
delay(2000);
}
delay(500);
}
