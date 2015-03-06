#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "winchControl.h"

#define DEBUG true

Gyro g;

void init(){
	initGyro(g, S2);
	calibrateGyro(g);
	resetWinchEncoder();
	servo[DUMP_SERVO] = DUMP_UP;
	servo[TUBE_SERVO] = TUBE_UP;
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
	wait1Msec(2000);

	// stops at the bottom
	move(STOP, 0, 200);

	// turn we can add in to make the program more accurate
	//gyroTurn(g, -5, 100);

	motor[RIGHT_DRIVE_MOTOR] = -10;
	motor[LEFT_DRIVE_MOTOR] = -10;
	wait1Msec(2000);
	moveTubeServo(DOWN);
	wait1Msec(1000);
	move(STOP, 0, 0);

	gyroTurn(g, 20, 75);
	gyroTurn(g, -20, 75);

	wait1Msec(500);

	servo[TUBE_SERVO] = TUBE_UP;

	//raises the winch
	//moveWinch(75, 4350);
	startAutoWinch(convertDegreesToTicks(GOAL_60 * 360));

	wait1Msec(6000);

	//dumps the balls
	servo[DUMP_SERVO] = DUMP_DOWN;

	//waits for balls to dump
	wait1Msec(1000);

	//raises the ramp again
	servo[DUMP_SERVO] = DUMP_UP;

	//lowers the winch again
	startAutoWinch(convertDegreesToTicks(0 * 360));
	while(true){}
}
