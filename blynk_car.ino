#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define MOV_VEL 5
#define MOV_DIR 0
#define MBP 4
#define MBD 2

char auth[] = "0e06d638802f462c891cf9b92a59be39";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CasaYisus";
char pass[] = "123456789";
int x,y;
int minRange = 412;
int maxRange = 612;
int neutral = 0;
int minSpeed = 0;
int maxSpeed = 1023;
int noSpeed = 0;


void moveControl()
{

  if(y > 512)
  { Serial.println("+512");
    digitalWrite(MOV_DIR,HIGH);
    analogWrite(MOV_VEL,map(y,512,1023,1,1023));
  }
  if(y < 512)
  { Serial.println("-512");
    digitalWrite(MOV_DIR,LOW);
    analogWrite(MOV_VEL,map(y,512,1023,1,1023));
  }
  if(y==512)
  {
        analogWrite(MOV_VEL,0);     
  }
  if(x > 512)
  { Serial.println("+512");
    digitalWrite(MBD,HIGH);
    analogWrite(MBP,maxSpeed);
  }
  if(x < 512)
  { Serial.println("-512");
    digitalWrite(MBD,LOW);
    analogWrite(MBP,maxSpeed);
  }
  if(x==512)
  {
        analogWrite(MBP,0);     
  }
  
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
  // initial settings for motors off and direction forward
  pinMode(MOV_VEL, OUTPUT);
  pinMode(MOV_DIR, OUTPUT);
  pinMode(MBD, OUTPUT);
  pinMode(MBP, OUTPUT);
 
  digitalWrite(MOV_VEL, LOW);
  digitalWrite(MBP, LOW);
  digitalWrite(MOV_DIR, HIGH);
  digitalWrite(MBD,HIGH);

 
 }


void loop()
{
  Blynk.run();

}




BLYNK_WRITE(V1)
{ 
  x = param[0].asInt();
  y = param[1].asInt();
  Serial.print("x value is: ");
  Serial.println(x);
  Serial.print("y value is: ");
  Serial.println(y);
  moveControl();
}
