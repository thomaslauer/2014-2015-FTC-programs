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
		move(BACKWARD, 50, 1300);
		gyroTurn(g, -20, 75);
		startAutoWinch(convertDegreesToTicks(GOAL_120 * 360));
		wait1Msec(10000);
		servo[DUMP_SERVO] = DUMP_DOWN;
		wait1Msec(2000);
		servo[DUMP_SERVO] = DUMP_UP;
		startAutoWinch(0);
	}

	while(true){move(STOP, 0, 0);}
}
