#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "esp8266-a4724.firebaseio.com"
#define FIREBASE_AUTH "RlZYi4Q59GZa8Boaex9ky7kRnFtOPBTe8QIeRtMw"
#define WIFI_SSID "NEST Secure"
#define WIFI_PASSWORD "nestNet100"

#define DEBUG true

void setup() {

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  if (DEBUG)
  {
      Serial.begin(19200);
      Serial.print("connecting");
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
      }
      Serial.println();
      Serial.print("connected: ");
      Serial.println(WiFi.localIP());
  }
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (DEBUG && Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

}

// EXAMPLE CODE
// Firebase.setFloat("number", 42.0);
// // handle error
// if (DEBUG && Firebase.failed()) {
//     Serial.print("setting /number failed:");
//     Serial.println(Firebase.error());  
//     return;
// }
// delay(1000);
// 
// // remove value
// Firebase.remove("number");
// delay(1000);
