#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
const char *ssid = "TP-Link_3972";  //ENTER YOUR WIFI ssid
const char *password = "37075880";  //ENTER YOUR WIFI password

/* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(D4, D3);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;		

#define gasSensor A0

void setup() {
connectWifi();
}


void loop() {
SendData();
}

//function to connect to wifi
void connectWifi(){
  delay(1000);
  Serial.begin(115200);
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
  unsigned long start;
  double lat_val, lng_val, alt_m_val;
  bool loc_valid, alt_valid, time_valid;
  int gas_value = analogRead(gasSensor);
  lat_val = gps.location.lat();	/* Get latitude data */
  loc_valid = gps.location.isValid();	/* Check if valid location data is available */
  lng_val = gps.location.lng();	/* Get longtitude data */
  /*if (!loc_valid){
    Serial.println("Latitude : *****");
    Serial.println("Longitude : *****");
  } else{

  }*/
  WiFiClient wifiClient;
  HTTPClient http;    //Declare object of class HTTPClient
  //Post Data
  String postData = "?lat=14.071877&long=120.630804";
  http.begin(wifiClient,"localhost",80,"http://localhost/summer_project/map/getdata.php");              //change the ip to your computer ip address
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
  delay(10000);
}