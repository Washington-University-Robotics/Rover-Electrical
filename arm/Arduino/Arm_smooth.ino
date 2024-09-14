//#include <Encoder.h>
#include <PID_v1.h>
#include <Adafruit_PWMServoDriver.h>

// DEFINING PINS
#define PWMA 9 
#define AIN1 5
#define AIN2 6
#define PPIN A0 // Potentiometer Pin
#define ENCA1 2
#define ENCA2 4

// ****DC MOTOR SHIT****
#define MAX_SPEED 200 // Max speed from DC motors (out of 255)
#define MIN_SPEED 0 // Min speed from DC motors (out of 255)
#define MAX_ANGLE 90 // Maximum angle arm can rotate to
#define SLOW_ANGLE 5 // Difference in angle where the arm will be about half speed


// ****SERVO MOTOR SHIT****
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  0 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOSTART 300 // This is the starting pulse length
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const int base = 0; // Pin number of base servo
const int elbow = 1; // Pin number of elbow servo


// TO CHANGE SPEED
unsigned const int delayer = 0; // Delays the frequency with which the servo position is updated - PROBABLY WILL NOT WORK AS WELL AS "increment"
unsigned const int increment = 2; // Assigns the amount that the servo position is updated with joysticks
unsigned const int equilibriumIncrement = 1; // Assigns the amount that the servo position is updated to return to equilibrium

int pwm_pre, pwm_now, target_pwm = SERVOSTART;

float diff = .2; // Accepted angle difference

float target, potent, output;

float speed;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  digitalWrite(AIN1,LOW); // Making dc motor go "forward"
  digitalWrite(AIN2,HIGH);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //target = myMap(analogRead(PPIN), 0, 1023, 0, 270); // Sets target angle to current angle
}

void loop() {
  if(Serial.available()){
    target = Serial.parseInt(); // saves target angle from serial input
  }

  // runServo();
  runDC();

}

void runServo() {
  target_pwm = myMap(target, 0, 180, SERVOMIN, SERVOMAX);
  pwm_now = .9*pwm_pre + .1*target_pwm;
  pwm_pre = pwm_now;
  pwm.setPWM(base, 0, pwm_now);
}

void runDC(){
  potent = myMap(analogRead(PPIN), 0, 1023, 0, 270); // Gets current angle of arm
  Serial.println(potent);
  
  // raising arm
  if(potent<(target-diff)){
    digitalWrite(AIN1,LOW); // Making dc motor go "forward"
    digitalWrite(AIN2,HIGH);
  }

  // lowering arm
  if(potent>(target+diff)){
    digitalWrite(AIN1,HIGH); // Making dc motor go "backwards"
    digitalWrite(AIN2,LOW);
  }

  // setting speed --- hopefully smooths
  smoothSpeed();

  analogWrite(PWMA,speed);  
}

void smoothSpeed() {
  // When the angle is within SLOW_ANGLE degrees we want to slow
  float difference = abs(potent-target); // takes angle distance to target
  speed = MAX_SPEED/(1+pow(3, -(difference-SLOW_ANGLE))); // REALLY scuffed logarithmic equation

  // OR much simpler
  // float steepness = ?;
  // speed = steepness*difference
}

// SOLVES PROBLEM OF MAP() ONLY TAKING AND RETURNING LONG VALUE
float myMap(float input, float in_min, float in_max, float out_min, float out_max){
  output = (out_max-out_min)*((input-in_min)/(in_max-in_min));
  output = output + out_min;
  return output;
}

