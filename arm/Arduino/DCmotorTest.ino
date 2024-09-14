#include <Encoder.h>


#define PWMA 12
#define AIN1 8
#define AIN2 7
#define ENCA1 2
#define ENCA2 4

int out;
int pos;

Encoder encA(ENCA1,ENCA2);

void setup() {
  // put your setup code here, to run once:



  Serial.begin(9600);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);

  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);

  analogWrite(PWMA,255); 
  delay(30000);
  analogWrite(PWMA, 0);

  delay(500);

  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);

  analogWrite(PWMA,255); 
  delay(30000);
  analogWrite(PWMA, 0);

  delay(500);


}

void loop() {

  


}
