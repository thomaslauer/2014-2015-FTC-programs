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
	//waitForStart();
	moveTubeServo(UP);
	raiseWinch();
}

task main()
{
	init();


	move(BACKWARD, 50, 1000);

	wait1Msec(500);
	gyroTurn(g, 33, 75);
	//motor[RIGHT_DRIVE_MOTOR]=-50;
	//motor[LEFT_DRIVE_MOTOR]=50;
	//wait1Msec(1000);
	move(BACKWARD, 50, 1600);

	//motor[RIGHT_DRIVE_MOTOR]=50;
	//motor[LEFT_DRIVE_MOTOR]=-50;
	//wait1Msec(1500);
	wait1Msec(500);
	gyroTurn(g, -33, 75);

	motor[RIGHT_DRIVE_MOTOR] = -40;
	motor[LEFT_DRIVE_MOTOR] = -40;
	wait1Msec(2300);

	moveTubeServo(DOWN);
	wait1Msec(100);

	move(STOP, 0);

	wait1Msec(1000);
	move(FORWARD, 100, 100);

	moveWinch(75, 2500);
	servo[DUMP_SERVO] = DUMP_DOWN;
	wait1Msec(3000);
	//return;
	servo[DUMP_SERVO] = DUMP_UP;
	wait1Msec(500);
	moveWinch(-75, 2000);
	move(FORWARD, 100, 2500);

	gyroTurn(g, -147, 75);

	move(BACKWARD, 50, 1400);



}
