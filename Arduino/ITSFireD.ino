#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <dht.h>

SoftwareSerial GPS_SoftSerial(3, 4); //(Rx, Tx) Create object named bt of the class SoftwareSerial

TinyGPSPlus gps; //Create an object named gps of the class TinyGPSPlus
#define dataPin D8 // Defines pin number to which the Temperature sensor is connected
dht DHT; // Creats a DHT object

#define gasSensor A0 //Defines MQ2 Sensor Analog Pin

volatile float minutes, seconds;
volatile int degree, secs, mins;

void setup() {
  Serial.begin(9600);	// Define baud rate for serial communication
  GPS_SoftSerial.begin(9600);	// Define baud rate for software serial communication
}

void loop() {
  smartDelay(10000);	// Generate precise delay of 10s
  unsigned long start;
  double lat_val, lng_val, alt_m_val;
  bool loc_valid, alt_valid, time_valid;
  int gas_value = analogRead(gasSensor);
  int readData = DHT.read11(dataPin);
  float t = DHT.temperature;
  lat_val = gps.location.lat();	// Get latitude data
  loc_valid = gps.location.isValid();	// Check if valid location data is available
  lng_val = gps.location.lng();	// Get longtitude data

  if (!loc_valid){
    Serial.println("Latitude : *****");
    Serial.println("Longitude : *****");
  }
  else{
    DegMinSec(lat_val);
    Serial.print("Latitude in Decimal Degrees : ");
    Serial.println(lat_val, 6);
    DegMinSec(lng_val);	// Convert the decimal degree value into degrees minutes seconds form
    Serial.print("Longitude in Decimal Degrees : ");
    Serial.println(lng_val, 6);
  }
  Serial.print("Carbon Monoxide = ");
  Serial.println(gas_value);
  Serial.print("Carbon Monoxide = ");
  Serial.print("Temperature = ");
	Serial.println(t);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())	// Encode data read from GPS while data is available on serial port
      gps.encode(GPS_SoftSerial.read());
// Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)	// Convert data in decimal degrees into degrees minutes seconds form
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}