#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Servo.h>
Servo Myservo;
int pos;
#define RELAY 5 //D8
const int IRSensor=4; //D2
int ir = 0;

BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "********************************************************";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "*********";
char pass[] = "*********";

void setup()
{
Blynk.begin(auth, ssid, pass);
Myservo.attach(2);
pinMode(RELAY, OUTPUT);
digitalWrite(RELAY,LOW);
const int IRSensor=4;
timer.setInterval(60000L, blynknotify); // Setup a function to be called every 10 second
timer.setInterval(1000L, blynklcd);
}

void servorun()
{
    
for(pos=0;pos<=180;pos+=3){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
  for(pos=180;pos>=0;pos-=3){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
}

void blynklcd()
{
  if (ir == LOW) {
    Blynk.virtualWrite(V5, "Fire Alert");
  }
   else {
    Blynk.virtualWrite(V5, "No Fire"); 
   }
}
void blynknotify() {
  if (ir == LOW) {
    Blynk.notify("FIRE ALERT");
   }
}

void loop()
{
Blynk.run();
timer.run();
ir = digitalRead(IRSensor);
if(ir == LOW) {  
servorun();  
digitalWrite(RELAY,LOW);
}
else { digitalWrite(RELAY,HIGH); }
}
