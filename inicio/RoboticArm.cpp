#include "RoboticArm.h"
#include "BraccioControl.h"
#include "ComsModule.h"

// The default value for the soft start
#define SOFT_START_LEVEL 0

//The software PWM is connected to PIN 12. You cannot use the pin 12 if you are using
//a Braccio shield V4 or newer
#define SOFT_START_CONTROL_PIN	12

//Low and High Limit Timeout for the Software PWM
#define LOW_LIMIT_TIMEOUT 2000
#define HIGH_LIMIT_TIMEOUT 6000

// Constructor (initialize Braccio object)
RoboticArm::RoboticArm(int step_delay)
{
	SetDelay(step_delay);
	base = new Joint(0, 180, 0);
	shoulder = new Joint(15, 165, 90);
	elbow = new Joint(0, 180, 180);
	wrist_ver = new Joint(0, 180, 130);
	wrist_rot = new Joint(0, 180, 90);
	gripper = new Joint(10, 73, 10);
	joints[0] = base;
	joints[1] = shoulder;
	joints[2] = elbow;
	joints[3] = wrist_ver;
	joints[4] = wrist_rot;
	joints[5] = gripper;
}

void RoboticArm::Start(bool soft_start)
{
	// Calling Braccio.begin(SOFT_START_DISABLED) the Softstart is disabled and you can use the pin 12
	if (soft_start) {
		pinMode(SOFT_START_CONTROL_PIN, OUTPUT);
		digitalWrite(SOFT_START_CONTROL_PIN, LOW);
	}

	// Initialization pin Servo motors
	base->GetServo().attach(8);
	shoulder->GetServo().attach(10);
	elbow->GetServo().attach(9);
	wrist_ver->GetServo().attach(6);
	wrist_rot->GetServo().attach(5);
	gripper->GetServo().attach(3);

	//Move each servo motor to initial position
	for (int i = 0; i < JT_NULL; i++) {
		joints[i]->GetServo().write(joints[i]->GetCurrentAngle());
		Serial.print("Joint ");
		Serial.print(i);
		Serial.print(": ");
		Serial.println(joints[i]->GetCurrentAngle());
	}

	if (soft_start) SoftStart(SOFT_START_LEVEL);
}

/*void RoboticArm::SetGripper(String gripper_state)
{
	if (gripper_state == "hopen") gripper->SetTargetAngle(10);
	else if (gripper_state == "hclose") gripper->SetTargetAngle(73);
}*/

void RoboticArm::SetDelay(int _step_delay)
{
	if (_step_delay > 30) _step_delay = 30;
	if (_step_delay < 10) _step_delay = 10;
	step_delay = _step_delay;
}

void RoboticArm::SetJointAngles(JointTypes joint_type, int angle)
{
	//int i = 0;
	//bool found = false;
	Serial.print("joint_type: ");
	Serial.print(joint_type);
	Serial.print("   angle: ");
	Serial.println(angle);
	if (joint_type < JT_NULL && joint_type >= 0) {
		if (angle < joints[joint_type]->GetMinAngle()) angle = joints[joint_type]->GetMinAngle();
		if (angle > joints[joint_type]->GetMaxAngle()) angle = joints[joint_type]->GetMaxAngle();
		joints[joint_type]->SetTargetAngle(angle);
		Serial.print("SET -> ");
		Serial.print(joint_type);
		Serial.print(": ");
		Serial.println(joints[joint_type]->GetCurrentAngle());
	}

	/*switch (joint_type)
	{
	case RoboticArm::JT_BASE:
		i = 0;
		found = true;
		break;
	case RoboticArm::JT_SHOULDER:
		i = 1;
		found = true;
		break;
	case RoboticArm::JT_ELBOW:
		i = 2;
		found = true;
		break;
	case RoboticArm::JT_WRIST_VER:
		i = 3;
		found = true;
		break;
	case RoboticArm::JT_WRIST_ROT:
		i = 4;
		found = true;
		break;
	case RoboticArm::JT_GRIPPER:
		i = 5;
		found = true;
		break;
	case RoboticArm::JT_NULL:
		break;
	default:
		break;
	}*/


	/*bool found = false;
	int i;
	for (i = 0; i < 6; i++)
	{
		if (servo_name == joints[i]->GetName())
		{
			found = true;
			break;
		}
	}*/

	/*if (found)
	{
		if (angle < joints[i]->GetMinAngle()) angle = joints[i]->GetMinAngle();
		if (angle > joints[i]->GetMaxAngle()) angle = joints[i]->GetMaxAngle();
		joints[i]->SetTargetAngle(angle);
		Serial.print("SET -> ");
		//Serial.print(joints[i]->GetName());
		Serial.print(joint_type);
		Serial.print(": ");
		Serial.println(joints[i]->GetCurrentAngle());
	}*/
}

int RoboticArm::GetCurrentAngles(JointTypes joint_type)
{
	int ret = -1;

	if (joint_type < JT_NULL && joint_type >= 0) {
		ret = joints[joint_type]->GetCurrentAngle();
	}

	/*switch (joint_type)
	{
	case RoboticArm::JT_BASE:
		ret = joints[0]->GetCurrentAngle();
		break;
	case RoboticArm::JT_SHOULDER:
		ret = joints[1]->GetCurrentAngle();
		break;
	case RoboticArm::JT_ELBOW:
		ret = joints[2]->GetCurrentAngle();
		break;
	case RoboticArm::JT_WRIST_VER:
		ret = joints[3]->GetCurrentAngle();
		break;
	case RoboticArm::JT_WRIST_ROT:
		ret = joints[4]->GetCurrentAngle();
		break;
	case RoboticArm::JT_GRIPPER:
		ret = joints[5]->GetCurrentAngle();
		break;
	case RoboticArm::JT_NULL:
		break;
	default:
		break;
	}*/

	return ret;

	/*bool found = false;
	int i;
	for (i = 0; i < 6; i++)
	{
		if (servo_name == joints[i]->GetName())
		{
			found = true;
			break;
		}
	}

	if (found) return (joints[i]->GetCurrentAngle());
	else return -1;*/
}

void RoboticArm::Move()
{
	moving = false;
	//For each servo motor if next degree is not the same of the previuos than do the movement
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

			Serial.print("Moved--> ");
			Serial.print(i);
			Serial.print(": ");
			Serial.println(joints[i]->GetCurrentAngle());
		}
	}

	if (moving) {
		send_message = true;
	}

	/// TOOD: take into account the other types of communication you have implemented, not only BT
	//If a bluettoth connection exists, on last loop robot was moved and on current loop nothing was moved
	if ((braccio.coms_module.GetComsState(ComsModule::CommTypes::CT_BLUETOOTH) == Communication::S_CONNECTED) && !moving && send_message)
	{
		Serial.println("Sent Free");
		braccio.coms_module.SendData("Free", ComsModule::CommTypes::CT_BLUETOOTH);
		//Serial.println(braccio.robot.BuildStringCurrentAngles());
		//braccio.coms_module.SendData(braccio.robot.BuildStringCurrentAngles(), ComsModule::CommTypes::CT_BLUETOOTH);
		send_message = false;
	}

	//delay to let finish the little movement
	delay(step_delay);
	delay(500);
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
