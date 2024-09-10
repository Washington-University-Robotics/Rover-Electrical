#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  0 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOSTART 300 // This is the starting pulse length
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const int base = 1; // Number of base servo
const int neck = 0; // Number of neckservo

bool equil = false; // checks whether to move servos back to equilibrium

int basePulse, neckPulse = SERVOSTART; // Sets starting point of the base and neck motors

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
    equil = false;
    float neckRead, baseRead;
    byte buffer[16];

    // Read 16 bytes from serial input buffer
    Serial.readBytes(buffer, 16);

    memcpy(&neckRead, buffer,sizeof(float)); // Extract the reading from left joystick
    memcpy(&baseRead, buffer+sizeof(float), sizeof(float)); // Extract the reading from right joystick
    
    // Altering neck position positively or negatively
    if(neckRead>0) {
      if(neckPulse<SERVOMAX) neckPulse+=increment;
    }
    if(neckRead<0) {
      if(neckPulse>SERVOMIN) neckPulse+=-increment;
    }

    // Altering base position positively or negatively
    if(baseRead>0) {
      if(basePulse<SERVOMAX) basePulse+=increment;
    }
    if(baseRead<0) {
      if(basePulse>SERVOMIN) basePulse+=-increment;
    }
    
    if(baseRead == 0 && neckRead == 0) equil = true;
    
    
  }

  // Writing to servos by altering PWM length 
  pwm.setPWM(neck 0, neckPulse);
  pwm.setPWM(base, 0, basePulse);

  if(equil) equilibrium();
  delay(delayer);
}

// Moves base and neck towards equilibrium
void equilibrium() {
  if(basePulse>SERVOSTART) basePulse = basePulse - equilibriumIncrement;
  if(basePulse<SERVOSTART) basePulse = basePulse + equilibriumIncrement;

  if(neckPulse>SERVOSTART) neckPulse = neckPulse - equilibriumIncrement;
  if(neckPulse<SERVOSTART) neckPulse = neckPulse + equilibriumIncrement;
}

