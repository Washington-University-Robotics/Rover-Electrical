#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*
  NOTES
  - ROS should return 4 floats in this order: [left joystick from 1:-1, right joystick from 1:-1, square button that TOGGLES between 1 and anything, circle button that either toggles like square or sends a value of one when pressed]
  - Added two new functions (hopefully):
      > When square is toggled on, the arm will move back to equilibrium. DO NOT FORGET TO DO THIS BEFORE TURNING ARM OFF OR EMOTING
      > When circle button is pressed, or toggled on, (whichever you want) the arm will wave 
  - Only controls 2 degrees of rotation: BASE and ELBOW (Can add more in the future)
  - The speed of the arm can be changed, will definitely be needed as otherwise the arm is a little slow or jumpy
  - There will FOR SURE be kinks to work out but hopefully this code works. Read through comments if you're confused with anything's function or if there is an error.

*/


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  0 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOSTART 300 // This is the starting pulse length
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const int base = 1; // Number of base servo
const int elbow = 0; // Number of elbow servo

bool equil = false; // checks whether to move servos back to equilibrium

int basePulse, elbowPulse = SERVOSTART; // Sets starting point of the base and elbow motors

// TO CHANGE SPEED
unsigned const int delayer = 0; // Delays the frequency with which the servo position is updated - PROBABLY WILL NOT WORK AS WELL AS "increment"
unsigned const int increment = 2; // Assigns the amount that the servo position is updated with joysticks
unsigned const int equilibriumIncrement = 1; // Assigns the amount that the servo position is updated to return to equilibrium

void setup() {
  Serial.begin(9600);

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates


}

void loop() {
  if(Serial.available() >= 16){
    float elbowRead, baseRead, squareRead, circleRead;
    byte buffer[16];

    // Read 16 bytes from serial input buffer
    Serial.readBytes(buffer, 16);

    memcpy(&elbowRead, buffer,sizeof(float)); // Extract the reading from left joystick
    memcpy(&baseRead, buffer+sizeof(float), sizeof(float)); // Extract the reading from right joystick
    memcpy(&squareRead, buffer+(2*sizeof(float)), sizeof(float)); // Extract the reading from square button
    memcpy(&circleRead, buffer+(3*sizeof(float)), sizeof(float)); // Extract the reading from circle button
    
    // Altering elbow position positively or negatively
    if(elbowRead>0) {
      if(elbowPulse<SERVOMAX) elbowPulse+=increment;
    }
    if(elbowRead<0) {
      if(elbowPulse>SERVOMIN) elbowPulse+=-increment;
    }

    // Altering base position positively or negatively
    if(baseRead>0) {
      if(basePulse<SERVOMAX) basePulse+=increment;
    }
    if(baseRead<0) {
      if(basePulse>SERVOMIN) basePulse+=-increment;
    }
    
    // Moves back to equilibrium if 
    if(squareRead == 1){
      equil = true;
    }
    else equil = false;

    // Does a "wave"
    if(circleRead == 1){ 
      // Goes from equilibrium to 135 degrees
      for (uint16_t pulselen = SERVOSTART; pulselen < map(135, 0, 180, SERVOMIN, SERVOMAX); pulselen++) {
        pwm.setPWM(elbow, 0, pulselen);
      }

      delay(500);

      // Goes from 135 degrees to 45 degrees
      for (uint16_t pulselen = map(135, 0, 180, SERVOMIN, SERVOMAX); pulselen > map(45, 0, 180, SERVOMIN, SERVOMAX); pulselen--) {
        pwm.setPWM(elbow, 0, pulselen);
      }

      // Goes from 45 degrees to equilibrium
      for (uint16_t pulselen = map(45, 0, 180, SERVOMIN, SERVOMAX); pulselen < SERVOSTART; pulselen++) {
        pwm.setPWM(elbow, 0, pulselen);
      }

    }
    
  }

  // Writing to servos by altering PWM length 
  pwm.setPWM(elbow, 0, elbowPulse);
  pwm.setPWM(base, 0, basePulse);

  if(equil) equilibrium();
  delay(delayer);
}

// Moves base and elbow towards equilibrium
void equilibrium() {
  if(basePulse>SERVOSTART) basePulse = basePulse - equilibriumIncrement;
  if(basePulse<SERVOSTART) basePulse = basePulse + equilibriumIncrement;

  if(elbowPulse>SERVOSTART) elbowPulse = elbowPulse - equilibriumIncrement;
  if(elbowPulse<SERVOSTART) elbowPulse = elbowPulse + equilibriumIncrement;
}

