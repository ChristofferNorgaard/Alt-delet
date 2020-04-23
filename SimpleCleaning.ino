#include <AccelStepper.h>
#include <MultiStepper.h>
#include <utility> // std::pair, std::make_pair
AccelStepper stepper1(AccelStepper::FULL2WIRE, 6, 7);
AccelStepper stepper2(AccelStepper::FULL2WIRE, 4, 5);

MultiStepper steppers;
//Config
/*
 * stepper 1 big motor in x direction
 * stepper 2 small motor in y direction
 * 
 * 
 * Table looks like this
 *             MinY switch
 *            ↓
*             _______________________________________
MinX switch →| →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→↓|←MaxX switch
*            | ↓←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←|
*            | →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→↓|
*            | ↓←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←|
*            | →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→↓|
*            | ↓←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←|
             | →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→↓|
*            | ↓←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←|
*            | →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→↓|
*            |______________________________________|
                                                  ↑
                                                  MaxY switch
Na tabli je narisana pot brisanja in pozicija stikal.
 */

//this should probably go into another Config file
int Steppper1maxSpped = 3200;
int Steppper2maxSpped = 3200;
int Steppper1Acceleration = 800;
int Steppper2Acceleration = 800;
int gobSize = 100;
std::pair<int> mes struct EndPins
{
  byte MinX;
  byte MaxX;
  byte MinY;
  byte MaxY;
}

void
steper_setup(AccelStepper steper, Steppper1maxSpped, Steppper1Acceleration)
{
  stepper1.setMaxSpeed(Steppper1maxSpped);
  stepper1.setAcceleration(Steppper1Acceleration);
}

std::pair<int> MessureBoard(EndPins endpins, AccelStepper step1, AccelStepper step2)
{
  /* Messuring gre po tem postopku

V prvem koraku gre program do Minimalnih tock
  
  *             MinY switch
 *            ↓
*             _______________________________________
MinX switch →| ←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←← |←MaxX switch
*            | ↑                                    |
*            | ↑                                    |
*            | ↑                                    |
*            | ↑                                    |
*            | ↑                                    |
*            | ↑                                    |
*            | ↑                                    |
*            | ↑                                    |
*            |______________________________________|
                                                  ↑
                                                  MaxY switch
  Potem pa najprej do MaxX in pri tem meri kolicino stepov, ki jih potrebuje, nato pa se dol do MaxY
  
    *             MinY switch
 *            ↓
*             _______________________________________
MinX switch →| →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→↓|←MaxX switch
*            |                                     ↓|
*            |                                     ↓|
*            |                                     ↓|
*            |                                     ↓|
*            |                                     ↓|
*            |                                     ↓|
*            |                                     ↓|
*            |                                     ↓|
*            |______________________________________|
                                                  ↑
                                                  MaxY switch
  */
  int stepsX = 0;
  int stepsY = 0;
  //homing steppers to 0,0
  step1.setSpeed(Steppper1maxSpped * -1) while (digitalRead(endpins.MinX) == LOW)
  {
    step1.step();
  }
  step2.setSpeed(Steppper1maxSpped * -1) while (digitalRead(endpins.MinY) == LOW)
  {
    step2.step();
  }
  //mesuring to maximum position x
  while (digitalRead(endpins.MaxX) == HIGH)
  {
    step1.step();
    stepX++;
  }
  //mesuring to position max y
  step2.setSpeed(Steppper1maxSpped);
  while (digitalRead(endpins.MaxY) == HIGH)
  {
    step2.step();
    stepX++;
  }

  return std::make_pair(stepsX, stepsY);
}

setup()
{
  //setup for motors
  steper_setup(stepper1);
  steper_setup(stepper2);
  //adding motors to multisteper controler
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  mes = MessureBoard(stepper1, stepper2)
}

// StopCheck handles all actions that must stop motors imidiatly
bool StopCheck()
{
  //any of switches high
  return (digitalRead(endpins.MinX) == HIGH || digitalRead(endpins.MinY) == HIGH || digitalRead(endpins.MaxX) == HIGH || digitalRead(endpins.MaxY) == HIGH)
}
int runSteppers()
{
  while (steppers.run() == true)
  {
    //in event of detecting end switching
    if (stopCheck())
    {
      stepper1.stop();
      stepper2.stop();
      return -1
    }
  }

  return 1;
}
void Cleaning(std::pair<int> mes)
{
  long pos[2] = {0, 0} steppers.moveTo(pos)
                    runSteppers();
  //stevilo kolikokrat se mora goba premakniti dol za en svoj step.
  int times = mes.first / gobSize;
  //na koncu ostane se del, ki je manjsi od gobe same, a se mora premakniti dol.
  int rem = mes.first % gobSize;
  bool smer = 1;
  for (int i = 0; i < times; i++)
  {
    long pos[2] = {mes.first * smer, stepper2.targetPosition() + gobSize};
    steppers.moveTo(pos);
    runSteppers();
    smer = !smer;
  }
  long pos[2] = {mes.first * smer, stepper2.targetPosition() + rem};
  steppers.moveTo(pos);
  runSteppers();
}

void loop()
{
  Cleaning(mes)
}
