/*
The purpose of this file is to move linear servo with feedback loop from a potentiometer. 
*/

#include <Servo.h>

// DEFINING PINS
#define APIN 10 // Actuator Pin
#define PPIN A0 // Potentiometer Pin

#define SERVOMIN  1990 // This is the 'minimum' pulse length count (out of 4096) FULLY RETRACTED
#define SERVOSTART 1990 // This is the starting pulse length
#define SERVOMAX  1010 // This is the 'maximum' pulse length count (out of 4096) FULLY EXTENDED
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define POT0 250 // This is the value of the potentiometer that corresponds to 0 degrees
#define POT90 450  // This is the value of the potentiometer that corresponds to 90 degrees

// PID coefficients, magnitude will effect the increments that the servo is changed by
float kp = .5; // proportional coefficient (Difference from target angle-current angle, should be majority of input)
float ki = .01; // integral coefficient (should be very small, maybe not needed?)
float kd = 0; // derivative coefficient. (as speed decreases we want output to decrease? should be very small)

Servo actuator;

// TO CHANGE SPEED NOT USED IN THIS LOOP
unsigned const int delayer = 0; // Delays the frequency with which the servo position is updated - PROBABLY WILL NOT WORK AS WELL AS "increment"
unsigned const int increment = 2; // Assigns the amount that the servo position is updated with joysticks
unsigned const int equilibriumIncrement = 1; // Assigns the amount that the servo position is updated to return to equilibrium

float pwm_pre, pwm_now, target_pwm = SERVOSTART;

float angle_now;

float target, potent, output, diff, diff_sum, diff_diff, diff_prev;

bool debug = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  actuator.attach(APIN);
  actuator.writeMicroseconds(1700); 
  delay(3000);

  target = myMap(analogRead(PPIN), POT0, POT90, 0, 90); // Sets target angle to current angle
  Serial.println(target);
}

void loop() {
  if(Serial.available()) {
    target = Serial.parseInt(); // saves target angle from serial input (FIRST MUST TEST TO SEE RANGE OF ANGLES, PROBABLY VERY NARROW)
    Serial.println(target);
  }


  runServo();

}

void runServo() {
  angle_now = myMap(analogRead(PPIN), POT0, POT90, 0, 90); // Gets current angle of arm
  pwm_now = pid();
  if(debug) {
    Serial.print(pwm_now);
    Serial.print("\t");
    Serial.print(target);
    Serial.print("\t");
    Serial.println(angle_now);
  }
  
  // Setting boundaries for pwm_values incase of overflow
  if(pwm_now>SERVOMIN) pwm_now = SERVOMIN;
  if(pwm_now<SERVOMAX) pwm_now = SERVOMAX;
  
  actuator.write(pwm_now);
}


// SOLVES PROBLEM OF MAP() ONLY TAKING AND RETURNING LONG VALUE
float myMap(float input, float in_min, float in_max, float out_min, float out_max){
  output = (out_max-out_min)*((input-in_min)/(in_max-in_min));
  output = output + out_min;
  return output;
}

// "PID" Loop (Units are in degrees). Because as pwm increases the angle decreases, we want to subtract our PID values?
float pid(){
  diff = target - angle_now; // P 
  diff_sum += diff; // I 
  diff_diff = diff_prev - diff; // D
  diff_prev = diff;

  return pwm_now - (kp*diff + ki*diff_sum + kd*diff_diff);
}
