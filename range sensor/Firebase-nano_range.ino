/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
#include <FirebaseArduino.h>

#define FIREBASE_HOST "nodemcupir.firebaseio.com"
#define FIREBASE_AUTH "1TheXTgjPcbxFv8Akmjmld6rcFm5l3yxbaiBIsnG"
#define WIFI_SSID "TP-LINK_3880"
#define WIFI_PASSWORD "sid123456"

const int trigPin = 15;
const int echoPin = 13;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}
void loop() {
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

delay(1000);
}
