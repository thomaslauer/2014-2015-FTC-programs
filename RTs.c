#include "hardwareDefinitions.h"
#include "motorControl.h"

#define DEBUG false

Gyro g;

void init(){
	servo[DUMP_SERVO] = DUMP_UP;
	initGyro(g, S2);
	calibrateGyro(g);
	servo[DUMP_SERVO] = DUMP_UP;
	moveTubeServo(STORE);
}

task main()
{
	init();

	// if we are not debugging wait for the start
	if(!DEBUG)waitForStart();

	//move(BACKWARD, 100, 2200);

	// moves off of the ramp, we have the -90 because of uneven
	// weight in our robot
	motor[RIGHT_DRIVE_MOTOR] = -90;
	motor[LEFT_DRIVE_MOTOR] = -100;
	wait1Msec(2200);

	// stops at the bottom
	move(STOP, 0, 200);

	// turn we can add in to make the program more accurate
	gyroTurn(g, -5, 100);

	motor[RIGHT_DRIVE_MOTOR] = -20;
	motor[LEFT_DRIVE_MOTOR] = -20;

	moveTubeServo(DOWN);
	wait1Msec(1500);
	move(STOP, 0, 0);

	wait1Msec(500);

	//raises the winch
	moveWinch(75, 4350);

	//dumps the balls
	servo[DUMP_SERVO] = DUMP_DOWN;

	//waits for balls to dump
	wait1Msec(1000);

	//raises the ramp again
	servo[DUMP_SERVO] = DUMP_UP;

	//lowers the winch again
	moveWinch(-75, 3800);
}
