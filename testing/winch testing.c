#include "hardwareDefinitions.h"
#include "winchControl.h"

task main()
{
	resetWinchEncoder();
	startAutoWinch(convertDegreesToTicks(360 * GOAL_120));

	wait1Msec(10000);

	servo[DUMP_SERVO] = DUMP_DOWN;
	while(true);
}
