#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"

#define DEBUG false

Gyro g;

void init()
{
	servo[DUMP_SERVO] = DUMP_UP;
	initGyro(g, S2);
	calibrateGyro(g);
	if(!DEBUG)waitForStart();
	servo[DUMP_SERVO] = DUMP_UP;
	moveTubeServo(STORE);
}

task main()
{
	init();

	//progress forward moves robot out of parking zone
	move(BACKWARD, 50, 1000);

	wait1Msec(500);

	//using the gyro sensor, robot turns towards the ramp about 45 degrees
	gyroTurn(g, 42, 75);

	//progresses forward again, this time to align with
	//the proper column for the small tube
	move(BACKWARD, 50, 1400);

	wait1Msec(500);

	//using the gyro sensor, robot turns away from the ramp about 45 degrees
	gyroTurn(g, -39, 75);

	wait1Msec(500);

	//move forward towards the rolling goals
	move(BACKWARD, 50, 2000);

	//moves the rest of the way slowly as to not knock the tube away
	moveTubeServo(UP);
	move(BACKWARD, 15, 350);

	//moves a bit farther to ease into the tube
	moveTubeServo(DOWN);
	move(BACKWARD, 10, 100);

	wait1Msec(500);
	//raises the winch
	moveWinch(75, 2800);

	//dumps the balls
	servo[DUMP_SERVO] = DUMP_DOWN;

	//waits for balls to dump
	wait1Msec(1000);

	//raises the ramp again
	servo[DUMP_SERVO] = DUMP_UP;

	//lowers the winch again. 50 points!
	moveWinch(-75, 2300);
}
