/*
 * This Arduino Nano ESP32 code was developed by newbiely.com
 *
 * This Arduino Nano ESP32 code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/arduino-nano-esp32/arduino-nano-esp32-mqtt
 */

#include <WiFi.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char WIFI_SSID[] = "VLCIOT";     // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "tunel40_uc3m";  // CHANGE TO YOUR WIFI PASSWORD

const char MQTT_BROKER_ADRRESS[] = "test.mosquitto.org";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "Maximo_esp32";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                      // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";                      // CHANGE IT IF REQUIRED, empty if not required

// The MQTT topics that ESP32 should publish/subscribe
const char PUBLISH_TOPIC[] = "marselle";    // CHANGE IT AS YOU DESIRE
const char SUBSCRIBE_TOPIC[] = "prueba";  // CHANGE IT AS YOU DESIRE

const int PUBLISH_INTERVAL = 5000;  // 5 seconds

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

void setup() {
  Serial.begin(9600);
  // Configuracion DHT11
  Serial.println(F("DHTxx test!"));
  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Arduino Nano ESP32 - Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  connectToMQTT();
}

void loop() {
  // Obtain data from the sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }
  
  mqtt.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageHandler);

  Serial.print("Arduino Nano ESP32 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino Nano ESP32 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino Nano ESP32 - Subscribed to the topic: ");
  else
    Serial.print("Arduino Nano ESP32 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino Nano ESP32 - MQTT broker Connected!");
}

void sendToMQTT() {
  StaticJsonDocument<200> message;
  message["timestamp"] = millis();
  message["humedad (%)"] = dht.readHumidity();  // Or you can read data from other sensors
  message["temperatura (ºC)"] = dht.readTemperature();  // Or you can read data from other sensors
  char messageBuffer[512];
  serializeJson(message, messageBuffer);

  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.println("Arduino Nano ESP32 - sent to MQTT:");
  Serial.print("- topic: ");
  Serial.println(PUBLISH_TOPIC);
  Serial.print("- payload:");
  Serial.println(messageBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("Arduino Nano ESP32 - received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload:");
  Serial.println(payload);
}
