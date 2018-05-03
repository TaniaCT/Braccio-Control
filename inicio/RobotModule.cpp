#include "RobotModule.h"
#include "BraccioControl.h"
#include "ComsModule.h"

RobotModule::RobotModule()
{
}

void RobotModule::Start()
{
	//	Initialization of the robotic arm and set to -1 the values of all available joint positions
	arm.Start();
	for (int i = 0; i < NUMBERPOSITIONS*ELEMENTSPOS; i++) {
		positions[i] = -1;

		// Uncomment for debbuging purpose

		/*Serial.print("Position ");
		Serial.print(i);
		Serial.print(": ");
		Serial.println(positions[i]);*/
	}
}

void RobotModule::Update()
{
	// Update of the robotic arm data, which means moving the robot until the target angles are reached
	arm.Move();
}

void RobotModule::SetDelay(int step_delay)
{
	arm.SetDelay(step_delay);
}

void RobotModule::SetGripper(int gripper_state)
{
	// Set of the gripper target angles if possible.
	// If the possible states (0/1) are correct, if the current angles are equal to target ones, 
	// a flag of no movement will be sent to the movile app, if the connection allows it
	// If the current angles are not equal to target ones, the new target angles will be set
	if (gripper_state == 0) {
		if (arm.GetCurrentAngles(RoboticArm::JointTypes::JT_GRIPPER) == 10) {
			if (braccio.coms_module.GetComsState(ComsModule::CommTypes::CT_BLUETOOTH) == Communication::S_CONNECTED)
				braccio.coms_module.SendData("Free", ComsModule::CommTypes::CT_BLUETOOTH);
		}
		else arm.SetJointAngles(RoboticArm::JointTypes::JT_GRIPPER, 10);
	}
	else if (gripper_state == 1) {
		if (arm.GetCurrentAngles(RoboticArm::JointTypes::JT_GRIPPER) == 65) {
			if (braccio.coms_module.GetComsState(ComsModule::CommTypes::CT_BLUETOOTH) == Communication::S_CONNECTED)
				braccio.coms_module.SendData("Free", ComsModule::CommTypes::CT_BLUETOOTH);
		}
		else arm.SetJointAngles(RoboticArm::JointTypes::JT_GRIPPER, 65);
	}
}

void RobotModule::JoggingCommand(p2List<int> &list)
{
	// There are two modes of "Jogging" or manual control
	// The first one is by joint, which means that with an specified joint you can move it
	// to the left or to the right by adding or substracting values to the current angle.
	if (list[1] >= 0 && list[1] < 6) {
		// From the mobile, you will send 1/0/2, which means that joint will move towards
		// the maximum or minimum angle or will remain where it is
		if (list[2] == 2) {
			arm.SetJointAngles((RoboticArm::JointTypes)list[1], 180);
		}
		else if (list[2] == 1) arm.SetJointAngles((RoboticArm::JointTypes)list[1], 0);
		else if (list[2] == 0)
		{
			int curr_angle = arm.GetCurrentAngles((RoboticArm::JointTypes)list[1]);
			if (curr_angle != -1) arm.SetJointAngles((RoboticArm::JointTypes)list[1], curr_angle);
		}
	}
	// The second one is by coordenates axis XYZ, which means that with a selected axis, you
	// will be able to move the gripper all along that axis
	else if (list[1] >= 6 && list[1] < 9) {
		//TODO: Code to move the gripper along the X, Y or Z axis

	}
}

void RobotModule::MoveCommand(p2List<int>& list)
{
	// There are three modes of automatic control
	// The first one is by joint, which means that with an specified joint (indexed from 0 to 5), you 
	// can move it to an specifed angle.
	if (list[1] >= 0 && list[1] <= 5) {
		if (list[2] == arm.GetCurrentAngles((RoboticArm::JointTypes)list[1])) {
			if (braccio.coms_module.GetComsState(ComsModule::CommTypes::CT_BLUETOOTH) == Communication::S_CONNECTED)
				braccio.coms_module.SendData("Free", ComsModule::CommTypes::CT_BLUETOOTH);
		}
		else arm.SetJointAngles((RoboticArm::JointTypes)list[1], list[2]);
	}

	// The second one is by coordinates axis XYZ, which means that with a selected axis, you
	// will be able to move the gripper to an specified value, all along that axis
	else if (list[1] >= 6 && list[1] <= 8) {
		// TODO: Set of XYZ positions, and implementation of the algorithm that allows
		// the movement of the robot with this input.

		// In case the selectes values were the same as the current ones, a flag of no movement
		// will be sent, if the connection allows it
		if (braccio.coms_module.GetComsState(ComsModule::CommTypes::CT_BLUETOOTH) == Communication::S_CONNECTED)
			braccio.coms_module.SendData("Free", ComsModule::CommTypes::CT_BLUETOOTH);
	}

	// The third, and last one, is by joint position, which means that you will be able to move 
	// all robot joints, by the specification of a joint configuration, previously saved
	else if (list[1] == 9) {
		for (int i = 0; i < ELEMENTSPOS; i++) {
			if (positions[list[2] * 6 + i] >= 0) arm.SetJointAngles((RoboticArm::JointTypes)i, positions[list[2] * 6 + i]);
		}
	}
}

String RobotModule::BuildStringCurrentAngles()
{
	// Returns a string with the command "Response" followed by the current
	// angles of all joints, all separated by an space character
	String angles = "RESPONSE ";
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_BASE)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_SHOULDER)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_ELBOW)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_WRIST_VER)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_WRIST_ROT)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_GRIPPER)));

	return angles;
}

void RobotModule::SavePosition(p2List<int>& list)
{
	// There are four modes of managing joint positions
	// The first one consists in, given an index or name for the position,
	// the current angles will be saved
	if (list[1] == 0) {
		if (list[2] >= 0 && list[2] < NUMBERPOSITIONS) {
			for (int i = 0; i < ELEMENTSPOS; i++) {
				positions[list[2] * ELEMENTSPOS + i] = arm.GetCurrentAngles((RoboticArm::JointTypes)i);
			}
		}
	}

	// The second one consists in, given an index or name for the position,
	// the especified angles will be saved
	else if (list[1] == 1) {
		int posTokens = 3;
		if (list[2] >= 0 && list[2] < NUMBERPOSITIONS) {
			for (int i = 0; i < ELEMENTSPOS; i++) {
				positions[list[2] * ELEMENTSPOS + i] = list[posTokens];
				posTokens++;
			}
		}
	}

	// The third one consists in the removal of all saved positions
	else if (list[1] == 2) {
		for (int i = 0; i < NUMBERPOSITIONS*ELEMENTSPOS; i++) {
			positions[i] = -1;
		}
	}

	// The fourth, and last one, consists in, given an index or name for the position,
	// the angles that contains will be removed
	else if (list[1] == 3) {
		if (list[2] >= 0 && list[2] < NUMBERPOSITIONS) {
			for (int i = 0; i < ELEMENTSPOS; i++) {
				positions[list[2] * ELEMENTSPOS + i] = -1;
			}
		}
	}

	// Uncomment for debugging purposes
	/*for (int i = 0; i < NUMBERPOSITIONS*ELEMENTSPOS; i++) {
		Serial.print("Position ");
		Serial.print(i);
		Serial.print(": ");
		Serial.println(positions[i]);
	}*/
}

void RobotModule::StopProgram() {

	// In order to stop the movement, the current angles are set as target angles.
	for (int i = 0; i < 6; i++) {
		arm.SetJointAngles((RoboticArm::JointTypes)i, arm.GetCurrentAngles((RoboticArm::JointTypes)i));
	}
}

