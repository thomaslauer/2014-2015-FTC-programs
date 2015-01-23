#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"

Gyro g;
PID p;

void init()
{
	servo[DUMP_SERVO] = DUMP_UP;
	resetPositions();
	initGyro(g, S2);
	calibrateGyro(g);
}



task main()
{
	init();
	//waitForStart();
	moveTubeServo(UP);
	raiseWinch();

	move(BACKWARD, 50, 1000);
	motor[RIGHT_DRIVE_MOTOR]=-50;
	motor[LEFT_DRIVE_MOTOR]=50;
	wait1Msec(1000);
	move(BACKWARD, 50, 1000);
	motor[RIGHT_DRIVE_MOTOR]=50;
	motor[LEFT_DRIVE_MOTOR]=-50;
	wait1Msec(1500);
	move(BACKWARD, 50, 2500);
}
