
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);
const int flamePin = 11;
const int TH = A0;
int flame = HIGH;
double t = 0;
const int smokeA0 = A5;
int pm25;


void setup() {
  // put your setup code here, to run once:
  pinMode(flamePin, INPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  dht.begin();
 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  flame = digitalRead(flamePin);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int s = analogRead(smokeA0);

 
  Serial.print("Smoke: ");
  Serial.println(s);

    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" % ");
    
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" \xC2\xB0");
    Serial.println("C | ");
    
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.print(" \xC2\xB0");
    Serial.println("C | ");

  if (flame== LOW){
 
    Serial.println("Safe");
    delay(1000);
  }
  else {
Serial.println("Fire");
 delay(1000);
  }
}
