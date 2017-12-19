#include "RoboticArm.h"
#include "BraccioControl.h"

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
	base = new Joint("Base", 0, 180, 0);
	shoulder = new Joint("Shoulder", 15, 165, 90);
	elbow = new Joint("Elbow", 0, 180, 180);
	wrist_ver = new Joint("Wrist_ver", 0, 180, 130);
	wrist_rot = new Joint("Wrist_rot", 0, 180, 90);
	gripper = new Joint("Gripper", 10, 73, 10);
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
	for (int i = 0; i < 6; i++) {
		joints[i]->GetServo().write(joints[i]->GetCurrentAngle());
		Serial.print(joints[i]->GetName());
		Serial.print(": ");
		Serial.println(joints[i]->GetCurrentAngle());
	}

	if (soft_start) SoftStart(SOFT_START_LEVEL);
}

void RoboticArm::SetGripper(String gripper_state)
{
	if (gripper_state == "hopen") gripper->SetTargetAngle(10);
	else if (gripper_state == "hclose") gripper->SetTargetAngle(73);
}

void RoboticArm::SetDelay(int _step_delay)
{
	if (_step_delay > 30) _step_delay = 30;
	if (_step_delay < 10) _step_delay = 10;
	step_delay = _step_delay;
}

void RoboticArm::SetJointAngles(String servo_name, int angle)
{
	bool found = false;
	int i;
	for (i = 0; i < 6; i++)
	{
		if (servo_name == joints[i]->GetName())
		{
			found = true;
			break;
		}
	}

	if (found)
	{
		if (angle < joints[i]->GetMinAngle()) angle = joints[i]->GetMinAngle();
		if (angle > joints[i]->GetMaxAngle()) angle = joints[i]->GetMaxAngle();
		joints[i]->SetTargetAngle(angle);
		Serial.print("SET -> ");
		Serial.print(joints[i]->GetName());
		Serial.print(": ");
		Serial.println(joints[i]->GetCurrentAngle());
	}
}

int RoboticArm::GetCurrentAngles(String servo_name)
{
	bool found = false;
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
	else return -1;
}

void RoboticArm::Move()
{
  moving = false;
	//For each servo motor if next degree is not the same of the previuos than do the movement
	for (int i = 0; i < 6; i++)
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
			Serial.print(joints[i]->GetName());
			Serial.print(": ");
			Serial.println(joints[i]->GetCurrentAngle());
		}
	}

 if (moving) {
  send_message = true;
 }
  //If a bluettoth connection exists, on last loop robot was moved and on current loop nothing was moved
 if ((braccio.bt_module.GetBluetoothState() == 1)&& !moving && send_message)
 {
  Serial.println("Sent");
  Serial.println(braccio.robot.BuildStringCurrentAngles());
  braccio.bt_module.WriteBluetooth(braccio.robot.BuildStringCurrentAngles());
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
