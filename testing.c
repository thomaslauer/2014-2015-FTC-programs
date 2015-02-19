#include "hardwareDefinitions.h"
#include "motorControl.h"

Gyro g;

task main()
{
	servo[DUMP_SERVO] = DUMP_UP;
	initGyro(g, S2);
	calibrateGyro(g);
	gyroTurn(g, 90, 100);
	move(BACKWARD, 100, 1000);
}
