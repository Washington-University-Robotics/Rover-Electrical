#include <Encoder.h>
#include <PID_v1.h>

#define PWMA 9
#define AIN1 5
#define AIN2 6
#define PPIN A5
#define ENCA1 2
#define ENCA2 4

int speed = 0; // PWM input for motors

int out;
int pos;
long potent;

// SETTING UP PID STUFF
//Define Variables we'll be connecting to
double Setpoint, Input, Output, error;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

Encoder encA(ENCA1,ENCA2);

void setup() {
  // put your setup code here, to run once:



  Serial.begin(9600);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);

  // MORE PID SETUP STUFF
  Input = map(analogRead(PPIN), 0, 1023, 0, 180);
  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);
  Setpoint = 90;
}

void loop() {

  // speed = map(potent, 0, 1023, 0, 255);
  // Serial.print(potent);
  // Serial.print("\t");
  // Serial.println(speed);

  // analogWrite(PWMA,speed); 
  if(Serial.available()){
    Setpoint = Serial.parseFloat();
    Setpoint = 1000*Setpoint;
    Serial.println(Setpoint);
  }
  if
  Input = map(analogRead(PPIN), 0, 1023, 0, 180);
  myPID.Compute();
  Serial.print("Potentiometer Angle:  ");
  Serial.print(Input);
  Serial.print("      Error: ");
  Serial.println(Output);
  delay(1000);
}
