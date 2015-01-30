#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"
#include "Gyro.h"
#include "hitechnic-irseeker-v2.h"

Gyro g;
tHTIRS2 irSeeker;

void init()
{
	servo[DUMP_SERVO] = DUMP_UP;
	resetPositions();
	initGyro(g, S2);
	calibrateGyro(g);
	initSensor(&irSeeker, IR_PORT);
	irSeeker.mode = DSP_1200;
	waitForStart();
	raiseWinch();


}

task updateSensor()
{
	while(true)
	{
		readSensor(&irSeeker);
		if(irSeeker.acDirection == 5)
		{
			playTone(440, 1);
		}
	}
}

task main()
{
	init();
	startTask(updateSensor);
	move(FORWARD, 50, 1400);
	wait1Msec(500);
	gyroTurn(g, -100, 100);

	if(irSeeker.acDirection >= 5)
	{
		// turn and duump
		move(BACKWARD, 50, 850);
		wait1Msec(500);
		gyroTurn(g, 100, 50);
		wait1Msec(250);
		move(FORWARD, 75, 1000);
	}
	else
	{
		move(FORWARD, 50, 700);
		wait1Msec(500);
		gyroTurn(g, 100, 100);
		if(irSeeker.acDirection >= 5)
		{
			// duump here
		move(BACKWARD, 50, 850);
		wait1Msec(500);
		gyroTurn(g, 100, 50);
		wait1Msec(250);
		move(FORWARD, 75, 350);
		wait1Msec(250);
		gyroTurn(g, 100, 100);
		move(FORWARD, 75, 250);

		}
		else
		{

			move(FORWARD, 50, 700);
			wait1Msec(500);
			gyroTurn(g, 100, 100);



			// duump in the other one
			move(BACKWARD, 50, 850);
			wait1Msec(500);
			gyroTurn(g, 100, 50);
			wait1Msec(250);
			move(FORWARD, 75, 350);
			wait1Msec(500);
			gyroTurn(g, 100, 100);
			move(FORWARD, 100, 1000);
		}
	}

	move(STOP, 0);
	while(true)
	{
		displayTextLine(3, "%d", irSeeker.acDirection);
	}
	stopAllTasks();
}
