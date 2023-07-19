#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "DHT.h"
volatile float minutes, seconds;
volatile int degree, secs, mins;
const char *ssid = "aso";  //ENTER YOUR WIFI ssid
const char *password = "12345678";  //ENTER YOUR WIFI password
const int buzzer = 9;

/* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(D4, D3);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;		
#define DHTTYPE DHT11   // DHT 11
// DHT Sensor
uint8_t DHTPin = D8;
DHT dht(DHTPin, DHTTYPE);  
float temp; 

#define gasSensor A0

void setup() {
  dht.begin();
  pinMode(buzzer, OUTPUT);
  connectWifi();
}


void loop() {
  SendData();
}

//function to connect to wifi
void connectWifi(){
  delay(1000);
  Serial.begin(115200);
  GPS_SoftSerial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //If connection successful show IP address in serial monitor 
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}


//function to send sensor data 
void SendData() {
  smartDelay(10000);	// Generate precise delay of 10s
  unsigned long start;
  double lat_val, lng_val, alt_m_val;
  bool loc_valid, alt_valid, time_valid;
  temp = dht.readTemperature(); // Gets the values of the temperature
  int gas_value = analogRead(gasSensor);
  lat_val = gps.location.lat();	/* Get latitude data */
  loc_valid = gps.location.isValid();	/* Check if valid location data is available */
  lng_val = gps.location.lng();	/* Get longtitude data */
  if (!loc_valid){
    Serial.println("Latitude : *****");
    Serial.println("Longitude : *****");
  } else{
    if(gas_value<60 || temp<50){
      tone(buzzer, 5000);
      WiFiClient wifiClient;
      HTTPClient http;    //Declare object of class HTTPClient
      //Post Data
      String postData = "lat=" + String(lat_val) + "&long=" + String(lng_val);
      http.begin(wifiClient,"192.168.165.141",80,"http://localhost/summer_project/map/getdata.php");              //change the ip to your computer ip address
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
      
      int httpCode = http.POST(postData);   //Send the request
      String payload = http.getString();    //Get the response payload
    
      Serial.println(httpCode);   //Print HTTP return code
      Serial.println(payload);    //Print request response payload
    
      http.end();  //Close connection
      exit(0);
    }
  }
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