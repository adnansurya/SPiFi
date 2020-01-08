#include <SoftwareSerial.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define WIFI_SSID "SPiFi"
#define WIFI_PASSWORD "hologram"
#define FIREBASE_HOST "hologram-labs.firebaseio.com" 
#define FIREBASE_AUTH "69eHYKlRDrWsrqbs2M6dJkRDvJYJASEykyISUtOB"


FirebaseData firebaseData;
String switch1;
int LED = 0;

void setup() {
  // put your setup code here, to run once:
  switch1 = "OFF";
  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.getString(firebaseData, "/spifi/switch_1"))
  {
    //Success, then try to read the JSON payload value
    switch1 = firebaseData.stringData();
    Serial.println(switch1);
    if(switch1== "OFF"){
       digitalWrite(LED, LOW);
    }else{
        digitalWrite(LED, HIGH);
    }
    
    
  }else{
    Serial.println("Tidak ada data");
  }
}
