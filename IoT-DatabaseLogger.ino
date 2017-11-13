#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "wastetrackertest.firebaseio.com"
#define FIREBASE_AUTH "spMkq6t8LCClD5XhUccFx7CtiGrmVVBSQdahQq2E"
#define WIFI_SSID "NEST Secure"
#define WIFI_PASSWORD "nestNet100"

#define DEBUG true

int ledInput = A0;

int timePassed=0;
int resistance=20;
double Energy=0;
double total=0;
double gallonused=0;
double wtotal=0;
double trashmade=0;
double trtotal=0;

void setup() {
    
    pinMode(ledInput, INPUT);

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
    
  timePassed += 1;
  double recoTrash=10*timePassed;
  double randtrash=random(6,10);
  trashmade=trashmade+randtrash;
  double tratio=trashmade/recoTrash;
  double tdiff=1-tratio;
  double trtotal=trtotal+tdiff;
  int trashpoints=trtotal*(1/16);
 
  double recoWater=(3.3*timePassed);
  double randwater=random(3,5);
  gallonused=(gallonused+randwater);
  double wratio=(gallonused/recoWater);
  double wdiff=1-wratio;
  wtotal=wtotal+wdiff;
  int waterpoints=wtotal*0.15;


  double Voltage=analogRead(ledInput)*5.0/1024;
  double Power=(Voltage*Voltage/resistance);

  Energy= Energy+Power;
  double energyconsumed=100*Energy;
  double RecoValue=(100.0/24*timePassed);

  double ratio=energyconsumed/RecoValue;
  double difference=1-ratio;
  total=total+difference;
  int electricitypoints=total;

  // TODO make these values change properly in the database too
  //if (total<0)
  //{
  //  lcd.print("savings=");
  //  lcd.print(total*(-1));
  //  lcd.print("mWH");
  //}
  //else
  //{
  //  lcd.print("wastage=");
  //  lcd.print(total);
  //  lcd.print("mWH");
  //}

  // TODO Some of these values have different keys from what's being updated in the database
  Firebase.setFloat("Users/CodeDayUser/Time elapsed", 43.0);
  Firebase.setFloat("Users/CodeDayUser/Stats/Water/WaterUsed", gallonused);
  Firebase.setFloat("Users/CodeDayUser/Stats/Water/RecommendedUsage", recoWater);
  Firebase.setFloat("Users/CodeDayUser/Stats/Water/Net water Savings", wtotal);
  Firebase.setFloat("Users/CodeDayUser/Stats/Waste/WasteProduced", trashmade);
  Firebase.setFloat("Users/CodeDayUser/Stats/Waste/RecommendedWaste", recoTrash);
  Firebase.setFloat("Users/CodeDayUser/Stats/Waste/Net recycling", trtotal);
  Firebase.setFloat("Users/CodeDayUser/Stats/Electricity/Net energy used", energyconsumed);
  Firebase.setFloat("Users/CodeDayUser/Stats/Electricity/RecommendedUsage", RecoValue);
  Firebase.setFloat("Users/CodeDayUser/Stats/Electricity/ElectricityUsed", total);
  Firebase.setFloat("Users/CodeDayUser/Eco Points/Water Points", waterpoints);
  Firebase.setFloat("Users/CodeDayUser/Eco Points/Waste Points", trashpoints);
  Firebase.setFloat("Users/CodeDayUser/Eco Points/Electricity Points", electricitypoints);
  Firebase.setFloat("Users/CodeDayUser/Net Eco Points",(waterpoints+trashpoints+electricitypoints));

  // TEMPORARY DEBUG VALUES :)
  //int number = random(100);
  //// update value
  //Firebase.setFloat("number", number);
  //// handle error
  //if (DEBUG && Firebase.failed()) {
  //    Serial.print("setting /number failed:");
  //    Serial.println(Firebase.error());  
  //    return;
  //}
  delay(1000);

}
