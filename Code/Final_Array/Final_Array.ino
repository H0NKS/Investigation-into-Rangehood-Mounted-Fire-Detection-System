
//PM2.5 Library 
#include "Adafruit_PM25AQI.h"
// Temp/Humidity Sensor library
#include <DHT.h>
#include <SoftwareSerial.h>

// Temp/Humidity Sensor Pin Setup
#define DHTPIN 4
#define DHTTYPE DHT11 // DHT 11
// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);

//Srial Setup for PM2.5
SoftwareSerial pmSerial(2, 3);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

//Falame sensor pin
const int flamePin = 11;


//Smoke Sensor Pin
const int smokeA0 = A5;

//Variables
const int TH = A0;
int flame = HIGH;
double t = 0;


void setup() {
  // put your setup code here, to run once:

//PM2.5 Setup Code
Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Adafruit PMSA003I Air Quality Sensor");

  // Wait one second for sensor to boot up!
  delay(1000);

  // If using serial, initialize it and set baudrate before starting!
  // Uncomment one of the following
  //Serial1.begin(9600);
  pmSerial.begin(9600);

  // There are 3 options for connectivity!
  //if (! aqi.begin_I2C()) {      // connect to the sensor over I2C
  //if (! aqi.begin_UART(&Serial1)) { // connect to the sensor over hardware serial
  if (! aqi.begin_UART(&pmSerial)) { // connect to the sensor over software serial 
    Serial.println("Could not find PM 2.5 sensor!");
    while (1) delay(10);
  }

  Serial.println("PM25 found!");



//Other Sensor Setup Code 
  pinMode(flamePin, INPUT);
  pinMode(smokeA0, INPUT);
  dht.begin();
   
}


void loop() {
  // put your main code here, to run repeatedly:


    //Other Sensor Code
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

  //PM2.5 Code
   PM25_AQI_Data data;
  
  if (! aqi.read(&data)) {
    Serial.println("Could not read from AQI");
    delay(500);  // try again in a bit!
    return;
  }
  Serial.println("AQI reading success");

  Serial.println();
  Serial.println(F("---------------------------------------"));
  Serial.println(F("Concentration Units (standard)"));
  Serial.println(F("---------------------------------------"));
  Serial.print(F("PM 1.0: ")); Serial.print(data.pm10_standard);
  Serial.print(F("\t\tPM 2.5: ")); Serial.print(data.pm25_standard);
  Serial.print(F("\t\tPM 10: ")); Serial.println(data.pm100_standard);
  Serial.println(F("Concentration Units (environmental)"));
  Serial.println(F("---------------------------------------"));
  Serial.print(F("PM 1.0: ")); Serial.print(data.pm10_env);
  Serial.print(F("\t\tPM 2.5: ")); Serial.print(data.pm25_env);
  Serial.print(F("\t\tPM 10: ")); Serial.println(data.pm100_env);
  Serial.println(F("---------------------------------------"));
  Serial.print(F("Particles > 0.3um / 0.1L air:")); Serial.println(data.particles_03um);
  Serial.print(F("Particles > 0.5um / 0.1L air:")); Serial.println(data.particles_05um);
  Serial.print(F("Particles > 1.0um / 0.1L air:")); Serial.println(data.particles_10um);
  Serial.print(F("Particles > 2.5um / 0.1L air:")); Serial.println(data.particles_25um);
  Serial.print(F("Particles > 5.0um / 0.1L air:")); Serial.println(data.particles_50um);
  Serial.print(F("Particles > 10 um / 0.1L air:")); Serial.println(data.particles_100um);
  Serial.println(F("---------------------------------------"));



}
