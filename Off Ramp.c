#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"

Gyro g;

void init()
{
	initGyro(g, S2);
}

task main()
{
	init();
	//waitForStart();
	moveTubeServo(UP);
	raiseWinch();


	move(BACKWARD, 25);									//Move off the ramp
	wait1Msec(3500);
	move(STOP, 0);
	moveTubeServo(DOWN);								//Mandies shift down
	wait1Msec(1000);
	move(FORWARD, 25);									//Grab
	wait1Msec(200);
	move(RIGHT, 75);
	wait1Msec(1000);
	move(STOP, 0);
}
