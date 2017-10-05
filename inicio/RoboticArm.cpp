#include "RoboticArm.h"
#include "Braccio.h"

// Constructor plus simple assignation
RoboticArm::RoboticArm(int step_delay): step_delay(step_delay)
{
}


void RoboticArm::Start()
{
  braccio.begin();
}

void RoboticArm::SetGripper(GripperState state)
{
  if(state != GRIPPER_NULL)
  {
    if(state == GRIPPER_OPEN)
    {
      m6 = 10;
    }
    else if(state == GRIPPER_CLOSE)
    {
       m6 = 73;
    }
  }
}

void RoboticArm::Move()
{
  braccio.ServoMovement(step_delay,m1,m2,m3,m4,m5,m6);
}

