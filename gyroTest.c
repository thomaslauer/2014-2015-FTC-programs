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
	raiseWinch();
}
task main()
{
	init()
	gyroTurn(g, 90, 50);

}
