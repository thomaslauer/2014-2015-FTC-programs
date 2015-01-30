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
	waitForStart();
	moveTubeServo(UP);
	raiseWinch();

	move(BACKWARD, 25);
	//Move off the ramp
	wait1Msec(3300);
	moveTubeServo(DOWN);
	//Mandies shift down
	wait1Msec(200);
	move(STOP, 0);
	wait1Msec(1000);
	move(FORWARD, 25);
	//Situate the tube
	wait1Msec(200);
	move(STOP, 0);
	moveWinch(75, 3700);
	//Raise winch
	servo[DUMP_SERVO] = DUMP_DOWN;
	//Move door down to dump
	wait1Msec(3000);
	//wait so we don't break anything
	servo[DUMP_SERVO] = DUMP_UP;
	wait1Msec(500);
	//raises dump back up
	moveWinch(-75, 3200);
	//lowers winch back down as to not tip over
	wait1Msec (1000);
}
