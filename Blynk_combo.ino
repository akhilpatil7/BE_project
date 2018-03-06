#include <BlynkSimpleEsp8266.h>
#include <FirebaseArduino.h>
#include "DHT.h"
#include  <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
char ssid[] = "TP-LINK_3880";
char pass[] = "sid123456";
char auth[] = "3f72f769a9f34eaaa733d3df5d3dcfb4";
//DHT
#define DHTPIN 0    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//range
const int trigPin = 15;
const int echoPin = 13;
// defines variables
long duration;
int distance;

int inputPin = 5;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
BlynkTimer timer;


#define FIREBASE_HOST "aquaponics-7796.firebaseio.com"
#define FIREBASE_AUTH "b8IeSWlnOeg1XiUjCxE0gpWMP3uRcnyLosyXDRzH"
#define WIFI_SSID "TP-LINK_3880"
#define WIFI_PASSWORD "sid123456"

int n = 0;

void myTimerEvent(){
  
  Blynk.virtualWrite(V0,digitalRead(13));
   Blynk.virtualWrite(V4,analogRead(A0));
  Blynk.virtualWrite(V1,digitalRead(5));
  Blynk.virtualWrite(V3,dht.readHumidity());
  Blynk.virtualWrite(V2,dht.readTemperature());
  
  }

void setup(){
  Serial.begin(9600);     // Communication started with 9600 baud
  //Serial.println ("WiFi Connected!");
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Blynk.begin(auth,ssid,pass);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
 pinMode(inputPin, INPUT);     // declare sensor as input
  //Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }
  dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  //Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
   timer.setInterval(1000L,myTimerEvent);
}
void loop(){//water_sensor
int sensor=analogRead(A0); // Incoming analog signal read and appointed sensor
//Serial.println(sensor);   //Wrote serial port
Firebase.setFloat ("Sensor",sensor);
//pir_sensor
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) { 
      // we have just turned on
      Firebase.setString("message", "Motion Started");
      // We only want to print on the output change, not state
      pirState = HIGH;
      Serial.print("BC");
    }
  } else {
    //digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Firebase.setString("message", "Motion Ended");
      // We only want to print on the output change, not state
      pirState = LOW;
      Serial.print("MC");
    }
  }
  //range_sensor
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Firebase.setFloat ("Distance",distance);
 
//delay(200);}
float h = dht.readHumidity();
  
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  Serial.println(t);
  Serial.println(h);
  //delay(200);
delay(1000);
// append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
  Blynk.run();
  timer.run();
}
