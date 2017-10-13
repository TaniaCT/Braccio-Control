#include "RoboticArm.h"
#include "Arduino.h"

// The default value for the soft start
#define SOFT_START_LEVEL 0

//The software PWM is connected to PIN 12. You cannot use the pin 12 if you are using
//a Braccio shield V4 or newer
#define SOFT_START_CONTROL_PIN	12

//Low and High Limit Timeout for the Software PWM
#define LOW_LIMIT_TIMEOUT 2000
#define HIGH_LIMIT_TIMEOUT 6000


// Constructor (initialize Braccio object) plus simple assignation
RoboticArm::RoboticArm(int step_delay)
{
	SetDelay(step_delay);
}


void RoboticArm::Start(bool soft_start)
{
  ///Serial.print("He entrado al Arm.begin. \n");
	// Calling Braccio.begin(SOFT_START_DISABLED) the Softstart is disabled and you can use the pin 12
	if (soft_start) {
		pinMode(SOFT_START_CONTROL_PIN, OUTPUT);
		digitalWrite(SOFT_START_CONTROL_PIN, LOW);
	}

	// Initialization pin Servo motors
	base.attach(11);
	shoulder.attach(10);
	elbow.attach(9);
	wrist_ver.attach(6);
	wrist_rot.attach(5);
	gripper.attach(3);

	// Set initial position/degree
	base_angle = 0;
	shoulder_angle = 45;
	elbow_angle = 180;
	wrist_ver_angle = 180;
	wrist_rot_angle = 90;
	gripper_angle = 10;

	//Move each servo motor to initial position
	base.write(base_angle);
	shoulder.write(shoulder_angle);
	elbow.write(elbow_angle);
	wrist_ver.write(wrist_ver_angle);
	wrist_rot.write(wrist_rot_angle);
	gripper.write(gripper_angle);


	if (soft_start)
		SoftStart(SOFT_START_LEVEL);

  ///Serial.print("He salido del Arm.begin. \n");
}

void RoboticArm::SetGripper(GripperState state)
{
	switch (state)
	{
	case GRIPPER_NULL:
		break;
	case GRIPPER_OPEN:
		target_gripper_angle = 10;
		break;
	case GRIPPER_CLOSE:
		target_gripper_angle = 73;
		break;
	default:
		break;
	}
}

void RoboticArm::SetDelay(int _step_delay)
{
	if (_step_delay > 30) _step_delay = 30;
	if (_step_delay < 10) _step_delay = 10;
	step_delay = _step_delay;
}

void RoboticArm::SetAngles(Servos servos, int angle)
{
	switch (servos)
	{
	case S_BASE:
		target_base_angle = angle;
		break;
	case S_SHOULDER:
		target_shoulder_angle = angle;
		break;
	case S_ELBOW:
		target_gripper_angle = angle;
		break;
	case S_WRIST_VER:
		target_wrist_ver_angle = angle;
		break;
	case S_WRIST_ROT:
		target_wrist_rot_angle = angle;
		break;
	default:
		break;
	}
}

void RoboticArm::Move()
{
	// Check values, to avoid dangerous positions for the Braccio
	if (target_base_angle < 0) target_base_angle = 0;
	if (target_base_angle > 180) target_base_angle = 180;
	if (target_shoulder_angle < 15) target_shoulder_angle = 15;
	if (target_shoulder_angle > 165) target_shoulder_angle = 165;
	if (target_elbow_angle < 0) target_elbow_angle = 0;
	if (target_elbow_angle > 180) target_elbow_angle = 180;
	if (target_wrist_ver_angle < 0) target_wrist_ver_angle = 0;
	if (target_wrist_ver_angle > 180) target_wrist_ver_angle = 180;
	if (target_wrist_rot_angle < 0) target_wrist_rot_angle = 0;
	if (target_wrist_rot_angle > 180) target_wrist_rot_angle = 180;
	if (target_gripper_angle < 10) target_gripper_angle = 10;
	if (target_gripper_angle > 73) target_gripper_angle = 73;

	//For each servo motor if next degree is not the same of the previuos than do the movement		
	if (target_base_angle != base_angle)
	{
		//One step ahead
		if (target_base_angle > base_angle) {
			base_angle++;
		}
		//One step beyond
		if (target_base_angle < base_angle) {
			base_angle--;
		}
		base.write(base_angle);
	}

	if (target_shoulder_angle != shoulder_angle)
	{
		//One step ahead
		if (target_shoulder_angle > shoulder_angle) {
			shoulder_angle++;
		}
		//One step beyond
		if (target_shoulder_angle < shoulder_angle) {
			shoulder_angle--;
		}
		shoulder.write(shoulder_angle);
	}

	if (target_elbow_angle != elbow_angle)
	{
		//One step ahead
		if (target_elbow_angle > elbow_angle) {
			elbow_angle++;
		}
		//One step beyond
		if (target_elbow_angle < elbow_angle) {
			elbow_angle--;
		}
		elbow.write(elbow_angle);
	}

	if (target_wrist_ver_angle != wrist_ver_angle)
	{
		//One step ahead
		if (target_wrist_ver_angle > wrist_ver_angle) {
			wrist_ver_angle++;
		}
		//One step beyond
		if (target_wrist_ver_angle < wrist_ver_angle) {
			wrist_ver_angle--;
		}
		wrist_rot.write(wrist_ver_angle);
	}

	if (target_wrist_rot_angle != wrist_rot_angle)
	{
		//One step ahead
		if (target_wrist_rot_angle > wrist_rot_angle) {
			wrist_rot_angle++;
		}
		//One step beyond
		if (target_wrist_rot_angle < wrist_rot_angle) {
			wrist_rot_angle--;
		}
		wrist_ver.write(wrist_rot_angle);
	}

	if (target_gripper_angle != gripper_angle)
	{
		if (target_gripper_angle > gripper_angle) {
			gripper_angle++;
		}
		//One step beyond
		if (target_gripper_angle < gripper_angle) {
			gripper_angle--;
		}
		gripper.write(gripper_angle);
	}

	//delay to let finish the little movement
	delay(step_delay);
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

