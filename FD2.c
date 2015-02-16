#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"

Gyro g;

void init()
{
	servo[DUMP_SERVO] = DUMP_UP;
	resetPositions();
	initGyro(g, S2);
	calibrateGyro(g);
	waitForStart();
	raiseWinch();
}


task main()
{
	init();
	move(BACKWARD, 100, 600);
	move(LEFT, 100, 500);
	move(BACKWARD, 100, 2000);
}
