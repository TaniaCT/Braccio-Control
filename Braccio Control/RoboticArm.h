#ifndef __ROBOTICARM__
#define __ROBOTICARM__

#include "Braccio.h"
#include "Servo.h"

enum HandState
{
  HAND_NULL,
  HAND_OPEN,
  HAND_CLOSE
};

class RoboticArm
{
public:
  RoboticArm(int step_delay);

  void Start();
  
  void Move();
  
  void SetHand(HandState state);

private:
  bool started = false;

  _Braccio braccio;

  int step_delay;
  int m1 = 0;
  int m2 = 45;
  int m3 = 180;
  int m4 = 180;
  int m5 = 90;
  int m6 = 10;  
  
};
#endif
