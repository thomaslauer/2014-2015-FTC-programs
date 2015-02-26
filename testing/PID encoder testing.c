#include "hardwareDefinitions.h"

#include "PID.h"

//TEST

int convertDegreesToTicks(int degrees)
{
	return ((float)degrees/360.0) * 1440.0;	//used to convert user input into someting the PID controler can use
}

task main()
{
	PID p;	//creates a new PID controler

	int target = convertDegreesToTicks(1 * 360);	//sets how far the motors will rotate

	initPID(p, 0.05, 0, 2, target, T2);

	int startingEncoder = nMotorEncoder[RIGHT_WINCH];	//sets the starting value of the PID

	while(true)
	{
		displayTextLine(3, "encoder: %d", nMotorEncoder[RIGHT_WINCH]);	//debuging text displayed on nxt
		int value = getPIDValue(p, nMotorEncoder[RIGHT_WINCH] - startingEncoder);
		motor[RIGHT_WINCH] = value;
		motor[RIGHT_WINCH] = value;
	}
}
