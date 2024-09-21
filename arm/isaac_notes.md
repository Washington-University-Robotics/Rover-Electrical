### Fall Semester

Learned the basics on servo motor operation (PWM, servo drivers, how to program/wire one, Adafruit library). Developed a program that takes an angle as input and rotates a servo motor by the specified amount as starter code for testing. In partnership with software team, created a program in Arduino that takes serial input from ROS and a PlayStation controller to move the arm. Worked with design team to come up with a general idea for an arm with 6 degrees of freedom. Also created MATLAB program to perform inverse kinematic calculations and communicate with arm through Arduino serial input (not very efficient).

- Discovered that Arduino will send large current to motor(s) upon upload, needs to be dissipated with other motors and/or resistors.
- Servos will lock out only after they have been written to and constant power is supplied.
- Torque of servo directly correlates with current draw.

## Spring Semester

This semester primarily focused on employing DC motors in the arm design. First learned how to alter the speed of a dc motor and read an encoder. Created program to change the speed of a dc motor based on potentiometer readings. Due to design team decision to use a linear actuator, created a PID loop that would smoothly turn a linear actuator until the arm reached a desired angle decided by serial input. Worked with design team to find desired motors and plan for testing arm but prototype built only had one degree of freedom from linear actuator.

- Gutted servo motor and mounted it to base of arm to act as a potentiometer (worked strangely well)
- Window motors will likely not have the strength to be effectively used in arm, better option is likely dc motors with high gear ratios.