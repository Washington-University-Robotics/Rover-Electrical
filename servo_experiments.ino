#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int startDegree = 90;

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
const int SERVOSTART = map(startDegree, 0, 180, SERVOMIN, SERVOMAX); // This is the 'start' pulse length count
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// Setting target degrees for servo motors
int shoulderDegree = 130;
int baseDegree = 180;
int elbowDegree = 150;

// declaring pulse length counters
int shoulderPulseLength;
int elbowPulseLength;
int basePulseLength;

// our servo # counter
const uint8_t shoulder = 1;
const uint8_t elbow = 2;
const uint8_t base = 0;

// Setting arm speed
unsigned const int delayer = 3;
unsigned const int increment = 1;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  shoulderPulseLength = map(shoulderDegree, 0, 180, SERVOMIN, SERVOMAX);
  basePulseLength = map(baseDegree, 0, 180, SERVOMIN, SERVOMAX);
  elbowPulseLength = map(elbowDegree, 0, 180, SERVOMIN, SERVOMAX);
  
  moveBase();
  

}


void loop() {
  // Drive each servo one at a time using setPWM()


  // // Drive each servo one at a time using writeMicroseconds(), it's not precise due to calculation rounding!
  // // The writeMicroseconds() function is used to mimic the Arduino Servo library writeMicroseconds() behavior. 
  // for (uint16_t microsec = USMIN; microsec < USMAX; microsec++) {
  //   pwm.writeMicroseconds(servonum, microsec);
  // }

  // delay(500);
  // for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
  //   pwm.writeMicroseconds(servonum, microsec);
  // }

  // delay(500);

  // servonum++;
  // if (servonum > 7) servonum = 0; // Testing the first 8 servo channels
}

void moveBase() {
  if(basePulseLength>SERVOSTART) {
    for (uint16_t pulselen = SERVOSTART; pulselen < basePulseLength; pulselen=pulselen+increment) {
      pwm.setPWM(base, 0, pulselen);
      delay(delayer);
    }

    delay(500);

    for (uint16_t pulselen = basePulseLength; pulselen > SERVOSTART; pulselen=pulselen-increment) {
      pwm.setPWM(base, 0, pulselen);
      delay(delayer);
    }
  }
  else{
    for (uint16_t pulselen = SERVOSTART; pulselen > basePulseLength; pulselen=pulselen-increment) {
      pwm.setPWM(base, 0, pulselen);
      delay(delayer);
    }

    delay(500);

    for (uint16_t pulselen = basePulseLength; pulselen < SERVOSTART; pulselen=pulselen+increment) {
      pwm.setPWM(base, 0, pulselen);
      delay(delayer);
    }
  }
}

void moveShoulder() {
  if(shoulderPulseLength>SERVOSTART) {
    for (uint16_t pulselen = SERVOSTART; pulselen < shoulderPulseLength; pulselen=pulselen+increment) {
      pwm.setPWM(shoulder, 0, pulselen);
      delay(delayer);
    }

    delay(500);

    for (uint16_t pulselen = shoulderPulseLength; pulselen > SERVOSTART; pulselen=pulselen-increment) {
      pwm.setPWM(shoulder, 0, pulselen);
      delay(delayer);
    }
  }
  else{
    for (uint16_t pulselen = SERVOSTART; pulselen > shoulderPulseLength; pulselen=pulselen-increment) {
      pwm.setPWM(shoulder, 0, pulselen);
      delay(delayer);
    }

    delay(500);

    for (uint16_t pulselen = shoulderPulseLength; pulselen < SERVOSTART; pulselen=pulselen+increment) {
      pwm.setPWM(shoulder, 0, pulselen);
      delay(delayer);
    }
  }
}

void moveElbow() {
  if(elbowPulseLength>SERVOSTART) {
    for (uint16_t pulselen = SERVOSTART; pulselen < elbowPulseLength; pulselen=pulselen+increment) {
      pwm.setPWM(elbow, 0, pulselen);
      delay(delayer);
    }

    delay(500);

    for (uint16_t pulselen = elbowPulseLength; pulselen > SERVOSTART; pulselen=pulselen-increment) {
      pwm.setPWM(elbow, 0, pulselen);
      delay(delayer);
    }
  }
  else{
    for (uint16_t pulselen = SERVOSTART; pulselen > elbowPulseLength; pulselen=pulselen-increment) {
      pwm.setPWM(elbow, 0, pulselen);
      delay(delayer);
    }

    delay(500);

    for (uint16_t pulselen = elbowPulseLength; pulselen < SERVOSTART; pulselen=pulselen+increment) {
      pwm.setPWM(elbow, 0, pulselen);
      delay(delayer);
    }
  }
}

void setZero(int motor) {
  for (uint16_t pulselen = SERVOSTART; pulselen > SERVOMIN; pulselen=pulselen-increment) {
    pwm.setPWM(motor, 0, pulselen);
    delay(delayer);
  }
}
