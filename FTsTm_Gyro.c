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
	//raiseWinch();
}

task main()
{
	init();


	move(BACKWARD, 50, 1000);
	//progress forward- moves robot out of parking zone
	wait1Msec(500);
	gyroTurn(g, 40, 75);
	//using the gyro sensor, robot turns towards the ramp about 45 degrees
	move(BACKWARD, 50, 1600);
	//progresses forward again, this time to align with
	//the proper column for the small tube
	wait1Msec(500);
	gyroTurn(g, -35, 75);
	//using the gyro sensor, robot turns towards the small tube
	motor[RIGHT_DRIVE_MOTOR] = -40;
	motor[LEFT_DRIVE_MOTOR] = -40;
	wait1Msec(2100);
	//Robot moves straight forward to the small tube
	moveTubeServo(DOWN);
	wait1Msec(300);
	//Mandies shift down, catching the small tube
	move(STOP, 0);
	//Stop all motion as to not break anything
	wait1Msec(1000);
	move(FORWARD, 100, 100);
	//situate the tube into optimum scoring position
	moveWinch(75, 2500);
	//raises the winch to desired height for the small tube
	servo[DUMP_SERVO] = DUMP_DOWN;
	//drops down the scoring door. 50 points!
	wait1Msec(3000);
	//return;
	servo[DUMP_SERVO] = DUMP_UP;
	//moves the scoring door back up- don't want to break anything
	wait1Msec(500);
	moveWinch(-75, 2000);
	//Lower winch. Don't want to tip over.
	move(FORWARD, 100, 2500);
	gyroTurn(g, -147, 75);
	move(BACKWARD, 50, 1400);
	//take the tube back to the scoring area. 20 points!
	//after this program, a maximum total of 70 points have been acquired!
}
