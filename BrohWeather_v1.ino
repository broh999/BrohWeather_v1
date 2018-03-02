/*********************************************************************
External Unit

*********************************************************************/

//#include <SPI.h>
#include <Wire.h>
#include <MD_DS3231.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>

// Select the mode of operation for the library
#define USE_POLLED      0 // polled only mode - use the return status from checkAlarm()
#define USE_POLLED_CB   1 // polled mode with callback - checkAlarm() will invoke the callback
#define USE_INTERRUPT   0 // external interrupt operation, set up for Arduino Uno pin PIN_INTERRUPT

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;



float tempmin = 60;
float pressuremBar;

void setup()   {
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}


void loop(){
          RTC.readTime();

          pressuremBar = (bmp.readPressure()); //Reading pressure from BMP in PA
          pressuremBar = pressuremBar / 100;   //Calculate pressure in mBar
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float hum = dht.readHumidity();
            // Read temperature as Celsius (the default)
            float temp = dht.readTemperature();
            
            
            
            /*if (temp < tempmin){
              tempmin=temp;
              Serial.print("Nuova tmin ");
              Serial.print(RTC.h);
              Serial.print(":");
              Serial.println(RTC.m);
            }*/

          
            // Send data to serial. Format is: HH:MM:SS,ExtTemp,IntTemp,ExtHum,Pressure
            rtctime(); 
            Serial.print("," + String(temp) + "," + bmp.readTemperature());
            Serial.print("," + String(hum) + ",");Serial.println(String(pressuremBar));

         
          delay(5000);
          
}

void rtctime(){
  //Prepare time format in hh:mm:ss
  if (RTC.h < 10) Serial.print("0");
  Serial.print(RTC.h);
  Serial.print(":");
  if (RTC.m < 10) Serial.print("0");
  Serial.print(RTC.m);
  Serial.print(":");
  if (RTC.s < 10) Serial.print("0");
  Serial.print(RTC.s);
}

