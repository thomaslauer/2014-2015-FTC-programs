#include "hardwareDefinitions.h"
#include "Gyro.h"
#include "motorControl.h"
#include "winchControl.h"

#define Testing false

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
		move(BACKWARD, 50, 1300);

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

		wait1Msec(250);

		//lowers the winch again
		startAutoWinch(0);
	}
	else
	{
		move(BACKWARD, 50, 800);

		wait1Msec(200);

		float avg = 0;
		for(int i = 0; i < 20; i++)
		{
			avg += SensorValue[ULTRASONIC_PORT];
			wait1Msec(10);
		}
		avg /= 20;
		displayTextLine(3, "AVG: %1.2f", avg);

		//while(true){}

		if(avg >= 70 && avg <= 90)
		{
			// position 1

			//moves forward, turns left and goes to face the center goal
			move(BACKWARD, 50, 200);
			wait1Msec(500);
			gyroTurn(g, -60, 100);
			wait1Msec(500);
			move(BACKWARD, 50, 1400);
			wait1Msec(500);
			gyroTurn(g, 70, 100);
			wait1Msec(500);
			move(BACKWARD, 50, 850);
			wait1Msec(500);
			gyroTurn(g, 96, 100);
			wait1Msec(500);
			move(FORWARD, 25, 222);
			startAutoWinch(convertDegreesToTicks(GOAL_120 * 360));
			wait1Msec(8000);
			servo[DUMP_SERVO] = DUMP_DOWN;
			wait1Msec(2000);
			servo[DUMP_SERVO] = DUMP_UP;
			wait1Msec(250);
			startAutoWinch(0);
		}
		else
		{
			//position 2

			wait1Msec(500);
			gyroTurn(g, -45, 100);
			wait1Msec(500);
			move(BACKWARD, 50, 1100);
			wait1Msec(500);
			gyroTurn(g, 90, 100);
			wait1Msec(500);
			move(FORWARD, 50, 150);

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

			wait1Msec(250);

			//lowers the winch again
			startAutoWinch(0);
		}
	}
	while(true){move(STOP, 0, 0);}
}
