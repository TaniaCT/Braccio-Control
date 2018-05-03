#include "RoboticArm.h"
#include "BraccioControl.h"
#include "ComsModule.h"

// The default value for the soft start is 0
#define SOFT_START_LEVEL 0

// The software PWM is connected to PIN 12. You cannot use the pin 12 if you are using
// a Braccio shield V4 or newer
#define SOFT_START_CONTROL_PIN	12

// Low and High Limit Timeout for the Software PWM
#define LOW_LIMIT_TIMEOUT 2000
#define HIGH_LIMIT_TIMEOUT 6000

RoboticArm::RoboticArm(int step_delay)
{
	// Initialization of available joints
	SetDelay(step_delay);
	base = new Joint(0, 180, 0);
	shoulder = new Joint(15, 165, 90);
	elbow = new Joint(0, 180, 90);
	wrist_ver = new Joint(0, 180, 90);
	wrist_rot = new Joint(0, 180, 90);

	//If 73 degrees are set as the maximum value, the servo will be damaged
	//gripper = new Joint(10, 73, 10); 

	gripper = new Joint(10, 65, 10);
	joints[0] = base;
	joints[1] = shoulder;
	joints[2] = elbow;
	joints[3] = wrist_ver;
	joints[4] = wrist_rot;
	joints[5] = gripper;
}

void RoboticArm::Start(bool soft_start)
{
	// Calling Braccio.Start(false) the Softstart is disabled and you can use the pin 12
	if (soft_start) {
		pinMode(SOFT_START_CONTROL_PIN, OUTPUT);
		digitalWrite(SOFT_START_CONTROL_PIN, LOW);
	}

	// Initialization pin Servo motors
	base->GetServo().attach(11);
	shoulder->GetServo().attach(10);
	elbow->GetServo().attach(9);
	wrist_ver->GetServo().attach(6);
	wrist_rot->GetServo().attach(5);
	gripper->GetServo().attach(3);

	//Move each servo motor to initial position
	for (int i = 0; i < JT_NULL; i++) {
		joints[i]->GetServo().write(joints[i]->GetCurrentAngle());

		// Uncomment for debugging purpose

		/*Serial.print("Joint ");
		Serial.print(i);
		Serial.print(": ");
		Serial.println(joints[i]->GetCurrentAngle());*/
	}

	if (soft_start) SoftStart(SOFT_START_LEVEL);
}

void RoboticArm::SetDelay(int _step_delay)
{
	// If the value is not inside the valid range, the limit values
	// will be set.
	if (_step_delay > 30) _step_delay = 30;
	if (_step_delay < 10) _step_delay = 10;
	step_delay = _step_delay;
}

void RoboticArm::SetJointAngles(JointTypes joint_type, int angle)
{
	// Uncomment for debugging purpose

	/*Serial.print("joint_type: ");
	Serial.print(joint_type);
	Serial.print("   angle: ");
	Serial.println(angle);*/

	// If the angle is not inside the range of the joint, the limit values
	// will be set.
	if (joint_type < JT_NULL && joint_type >= 0) {
		if (angle < joints[joint_type]->GetMinAngle()) angle = joints[joint_type]->GetMinAngle();
		if (angle > joints[joint_type]->GetMaxAngle()) angle = joints[joint_type]->GetMaxAngle();
		joints[joint_type]->SetTargetAngle(angle);

		// Uncomment for debugging purpose
		Serial.print("SET -> ");
		Serial.print(joint_type);
		Serial.print(": ");
		Serial.println(joints[joint_type]->GetCurrentAngle());
	}
}

int RoboticArm::GetCurrentAngles(JointTypes joint_type)
{
	// The return value will be -1 if the specified joint is not correct
	int ret = -1;

	if (joint_type < JT_NULL && joint_type >= 0) {
		ret = joints[joint_type]->GetCurrentAngle();
	}

	return ret;
}

void RoboticArm::Move()
{
	moving = false;
	//For each servomotor, if next degree is not the same of the previuos one, then perform the movement
	for (int i = 0; i < JT_NULL; i++)
	{
		int target_angle = joints[i]->GetTargetAngle();
		int current_angle = joints[i]->GetCurrentAngle();
		if (target_angle != current_angle)
		{
			moving = true;
			//One step ahead
			if (target_angle > current_angle) {
				current_angle++;
			}
			//One step beyond
			if (target_angle < current_angle) {
				current_angle--;
			}
			joints[i]->SetCurrentAngle(current_angle);
			joints[i]->GetServo().write(joints[i]->GetCurrentAngle());

			// Uncomment for debugging purpose
			Serial.print("Moved--> ");
			Serial.print(i);
			Serial.print(": ");
			Serial.println(joints[i]->GetCurrentAngle());
		}
	}

	if (moving) {
		send_message = true;
	}

	// If a bluettoth connection exists, on last loop robot was moved and on current loop nothing was moved
	if ((braccio.coms_module.GetComsState(ComsModule::CommTypes::CT_BLUETOOTH) == Communication::S_CONNECTED) && !moving && send_message)
	{
		// Uncomment for debugging purpose
		Serial.println("Movement finished");

		braccio.coms_module.SendData("Free", ComsModule::CommTypes::CT_BLUETOOTH);
		send_message = false;
	}

	// Delay to let finish the little movement
	delay(step_delay);

	// Delay to reduce de velocity of the movement
	delay(50);
}

// This function, used only with the Braccio Shield V4 and greater,
// turn ON the Braccio softly and save it from brokes.
// The SOFT_START_CONTROL_PIN is used as a software PWM
// @param soft_start_level: the minimum value is -70, default value is 0 (SOFT_START_DEFAULT)
void RoboticArm::SoftStart(int soft_start_level)
{
	long int tmp = millis();
	while (millis() - tmp < LOW_LIMIT_TIMEOUT)
		SoftwarePWM(80 + soft_start_level, 450 - soft_start_level);   //the sum should be 530usec	

	while (millis() - tmp < HIGH_LIMIT_TIMEOUT)
		SoftwarePWM(75 + soft_start_level, 430 - soft_start_level); //the sum should be 505usec

	digitalWrite(SOFT_START_CONTROL_PIN, HIGH);
}

// Software implementation of the PWM for the SOFT_START_CONTROL_PIN,HIGH
// @param high_time: the time in the logic level high
// @param low_time: the time in the logic level low
void RoboticArm::SoftwarePWM(int high_time, int low_time)
{
	digitalWrite(SOFT_START_CONTROL_PIN, HIGH);
	delayMicroseconds(high_time);
	digitalWrite(SOFT_START_CONTROL_PIN, LOW);
	delayMicroseconds(low_time);
}
