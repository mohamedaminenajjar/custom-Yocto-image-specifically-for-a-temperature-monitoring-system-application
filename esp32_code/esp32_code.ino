#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <string.h>

#define LED 2
float temp;

// DHT11 pin declaration
DHT dht(26, DHT11);

// Wi-Fi credentials
const char* ssid = "TOPNET_8E88";
const char* password = "1i4hm4k1d7";

// Raspberry Pi MQTT broker details
const char* mqtt_server = "192.168.1.25"; // Raspberry Pi IP address

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to Wi-Fi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT Broker...\n");
    if (client.connect("ESP32_Client_1")) {
      Serial.println("connected!");
      // Subscribe to the topic when connected
      client.subscribe("temp/topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  
  // Check if the message is from the specified topic
  if (strcmp(topic, "temp/topic") == 0) 
  {
    // Build the message from the payload
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }
  }
  Serial.println(message);
    // Check if the message is "led on"
    if (message.equals("led on")) // Use .equals() for string comparison
    {  
      pinMode(LED, OUTPUT);           // Ensure LED pin is set as output
      digitalWrite(LED, HIGH);        // Turn the LED on
      Serial.println("LED is ON");    // Optional: Print to Serial Monitor
      delay(7000);         // Ensure LED pin is set as output
      digitalWrite(LED, LOW);        // Turn the LED on
      Serial.println("LED is OFF");    // Optional: Print to Serial Monitor
    }
}


void setup() {
  dht.begin();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);  // Set the callback function
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  temp = dht.readTemperature();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C ");
  //delay(2000);

  String temp_string = String(temp);
  // Publishing message every 5 seconds
  //Serial.println("Publishing message to MQTT topic...");
  client.publish("temp/topic", temp_string.c_str());
  delay(1000);  // wait 5 seconds before publishing again
}
