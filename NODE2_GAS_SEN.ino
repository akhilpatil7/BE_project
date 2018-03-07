#include <BlynkSimpleEsp8266.h>
#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "aquaponics-7796.firebaseio.com"
#define FIREBASE_AUTH "b8IeSWlnOeg1XiUjCxE0gpWMP3uRcnyLosyXDRzH"
#define BLYNK_PRINT Serial
char ssid[] = "TP-LINK_3880";
char pass[] = "sid123456";
char auth[] = "3f72f769a9f34eaaa733d3df5d3dcfb4";

int input = A0;
int output = 7;
int th=500; // Set threshold level.
String airqual;

//BLYNK_READ(V1) {
//  Blynk.virtualWrite(V1, airqual);
//}

WidgetLCD lcd(V1);

void setup()
{
Serial.begin(9600);
//pinMode(output,OUTPUT);
//digitalWrite(output,LOW);
Blynk.begin(auth,ssid,pass);
Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}
void loop()
{
Serial.println(analogRead(input));
if(analogRead(input)>th)
{
//digitalWrite(output,HIGH);
Serial.println("HIGH");
airqual = "HIGH";
Firebase.setString("Air","HIGH");
 lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "HIGH"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
 // lcd.print(4, 1, "World");
}
else
{
//digitalWrite(output,LOW);
Serial.println("LOW");
airqual = "LOW";
Firebase.setString("Air","LOW");
lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "LOW"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
 
}
delay(500);
 Blynk.run();
}
