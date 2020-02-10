#include <Arduino.h>
#include <Stepper.h>
#include <Motor.h>

MotorControl::Motor(int stpPrRev, int PULpin, int DIRpin)
{
    Stepper myStepper(stepsPerRevolution, 7, 6);
    Mystepper = myStepper;
}
int MotorControl::norm(int steps, int pin_a, int pin_b)
{
}