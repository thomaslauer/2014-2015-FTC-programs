#include "hardwareDefinitions.h"
#include "Gyro.h"
#include "PID.h"
#include "motorControl.h"

task main()
{
	Gyro g;
	initGyro(g, S2);
	calibrateGyro(g);
	PID pid;

	initPID(pid, 3, 0.00000001, 3, T2);
	setPIDTarget(pid, 90);

	while(true)
	{
		float currentPidValue = getPIDValue(pid, g.heading);
		displayTextLine(1, "heading: %d", g.heading);
		displayTextLine(2, "PID error: %d", pid.lastError);
		displayTextLine(3, "value: %d", currentPidValue);
		move(RIGHT, currentPidValue);
		//wait1Msec(10);
		updateGyro(g);
	}
}
