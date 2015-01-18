#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"


void init()
{
}


task main()
{
	init();
	//waitForStart();
	moveTubeServo(UP);
	raiseWinch();


	move(BACKWARD, 25);
	wait1Msec(4000);
	move(STOP, 0);
	moveTubeServo(DOWN);
	wait1Msec(1000);
	move(FORWARD, 25);
	wait1Msec(500);
	move(STOP, 0);
}
