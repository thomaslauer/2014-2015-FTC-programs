#include "hardwareDefinitions.h"
#include "Gyro.h"
#include "motorControl.h"
#include "winchControl.h"

#define Testing true

Gyro g;

void initRobot()
{
	if(Testing){disableDiagnosticsDisplay(); eraseDisplay();}

	resetPositions();
	initGyro(g, S2);
	calibrateGyro(g);
	resetWinchEncoder();
}

task main()
{
	initRobot();
	if(!Testing){waitForStart();}

	float avg = 0;
	for(int i = 0; i < 20; i++)
	{
		avg += SensorValue[ULTRASONIC_PORT];
		wait1Msec(10);
	}
	avg /= 20;

	displayTextLine(3, "AVG: %1.2f", avg);

	if(avg >= 100 && avg <= 110)
	{
		// position 3

		//advances towards the center goal
		move(BACKWARD, 50, 1350);

		//stops to let robot settle
		wait1Msec(500);

		//minor turn to get aligned
		gyroTurn(g, -10, 100);

		//starts the winch moving up
		startAutoWinch(convertDegreesToTicks(GOAL_120 * 360));

		//waits for the winch to get up
		wait1Msec(8000);

		//moves the dump down to deposit balls
		servo[DUMP_SERVO] = DUMP_DOWN;

		//waits for balls to roll out
		wait1Msec(2000);

		//moves the dump back up
		servo[DUMP_SERVO] = DUMP_UP;

		//lowers the winch again
		startAutoWinch(0);
	}
	else if(avg == 255)
	{
		//position 2
		move(BACKWARD, 50, 800);
		wait1Msec(500);
		gyroTurn(g, -45, 100);
		wait1Msec(500);
		move(BACKWARD, 50, 1250);
		wait1Msec(500);
		gyroTurn(g, 90, 100);
		wait1Msec(500);
		move(BACKWARD, 50, 50);

		//starts the winch moving up
		startAutoWinch(convertDegreesToTicks(GOAL_120 * 360));

		//waits for the winch to get up
		wait1Msec(8000);

		//moves the dump down to deposit balls
		servo[DUMP_SERVO] = DUMP_DOWN;

		//waits for balls to roll out
		wait1Msec(2000);

		//moves the dump back up
		servo[DUMP_SERVO] = DUMP_UP;

		//lowers the winch again
		startAutoWinch(0);
	}
	else if(avg >= 120 && avg <= 130)
	{
		// position 1

		//moves forward, turns left and goes to face the center goal
		move(BACKWARD, 50, 1000);
		wait1Msec(500);
		gyroTurn(g, -60, 100);
		wait1Msec(500);
		move(BACKWARD, 50, 1400);
		wait1Msec(500);
		gyroTurn(g, 60, 100);
		wait1Msec(500);
		move(BACKWARD, 50, 800);
		wait1Msec(500);
		gyroTurn(g, 100, 100);
		wait1Msec(500);
		move(BACKWARD, 25, 200);
		startAutoWinch(convertDegreesToTicks(GOAL_120 * 360));
		wait1Msec(8000);
		servo[DUMP_SERVO] = DUMP_DOWN;
		wait1Msec(2000);
		servo[DUMP_SERVO] = DUMP_UP;
		startAutoWinch(0);
	}
	while(true){move(STOP, 0, 0);}
}
