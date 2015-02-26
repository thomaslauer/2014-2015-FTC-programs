#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"

Gyro g;

#define TESTING true

void init()
{
	hideTubeServos();
	servo[DUMP_SERVO] = DUMP_UP;
	//resetPositions();
	initGyro(g, S2);
	calibrateGyro(g);
	if(!TESTING) waitForStart();
	//moveTubeServo(UP);
	//raiseWinch();
}


task main()
{
	init();
	move(FORWARD, 100, 1000);
	gyroTurn(g, -70, 100);
	move(FORWARD, 100, 1900);
	moveTubeServo(DOWN);
}
