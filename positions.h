#pragma once
#pragma systemFile

//This file is used to define servos, servo positions, and motors

// the dumper servo on the schlorp tube
const TServoIndex DUMP_SERVO = servo1;
const int DUMP_UP = 0;
const int DUMP_DOWN = 140;

// right servo for grabbing tubes
const TServoIndex RIGHT_TUBE_SERVO = servo2;
const int RIGHT_TUBE_UP = 127;
const int RIGHT_TUBE_DOWN = 240;

// left servo for grabbing tubes
const TServoIndex LEFT_TUBE_SERVO = servo3;
const int LEFT_TUBE_UP = 127;
const int LEFT_TUBE_DOWN = 15;

// resets the positions of all the servos
void resetPositions()
{
	servo[DUMP_SERVO] = DUMP_UP;
}
