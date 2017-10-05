#include "RoboticArm.h"
#include "Braccio.h"

RoboticArm::RoboticArm(int step_delay): step_delay(step_delay)
{
}

void RoboticArm::Start()
{
  braccio.begin();
}

void RoboticArm::SetHand(HandState state)
{
  if(state != HAND_NULL)
  {
    if(state == HAND_OPEN)
    {
      m6 = 10;
    }
    else if(state == HAND_CLOSE)
    {
       m6 = 73;
    }
  }
}

void RoboticArm::Move()
{
  braccio.ServoMovement(step_delay,m1,m2,m3,m4,m5,m6);
}

