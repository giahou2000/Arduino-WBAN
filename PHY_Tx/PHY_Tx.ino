String sendMessage;
String receivedMessage;
#include "DHT.h"
  
//Define the temperature pin
#define DHTPIN 2
  
// Define the temperature sensor type
#define DHTTYPE DHT11
  
// Declare an object of type DHT
DHT dht(DHTPIN, DHTTYPE);





void setup() {
  Serial.begin(9600);    // Initialize the Serial monitor for debugging
  Serial1.begin(9600);   // Initialize Serial1 for sending data
    
  // Initialize the sensor DHT11
  dht.begin();
}




void loop() {

  //Read
  Serial.println("Temperature = " + String(dht.readTemperature())+" °C");
  
  sendMessage = String(dht.readTemperature());

  //Send
  Serial1.println(sendMessage);
  sendMessage = "";


  delay(10000);
}