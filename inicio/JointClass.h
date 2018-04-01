#ifndef __JOINTCLASS__
#define __JOINTCLASS__

#include <Servo.h>
#include "Arduino.h"

class Joint {
public:
	Joint(int min_angle, int max_angle, int current_angle);

	Servo GetServo(); 
	//String GetName();
	int GetMinAngle();
	int GetMaxAngle();
	int GetCurrentAngle();
	void SetCurrentAngle(int angle);
	int GetTargetAngle(); ///TODO: borrar si es innecesario
	void SetTargetAngle(int angle);

private:
	Servo servo;
	//String joint_name;
	int min_angle;
	int max_angle;
	int current_angle;
	int target_angle;
};

#endif 

