#pragma once
#pragma systemFile

//This file is used to define servos, servo positions, and motors

const TServoIndex DUMP_SERVO = servo1;
const int DUMP_UP = 0;
const int DUMP_DOWN = 140;

void resetPositions()
{
	servo[DUMP_SERVO] = DUMP_UP;
}
