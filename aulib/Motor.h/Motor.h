#include <Stepper.h>
#include "Arduino.h"
#ifndef Motor_h
#define Motor_h

/*
` A library created to ease the acceleration of servos
*/
class MotorControl
{
public:
  Motor(int stpPrRev, int PULpin, int DIRpin);
  int norm(int steps, int pin_a, int pin_b);
  int Acel(int steps, int a);

private:
  Stepper Mystepper;
}

#endif
