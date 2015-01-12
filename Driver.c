#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "driverUtils.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot()
{
  return;
}

// task to run driver 2 stuff
task scoring()
{
	while(true)
	{
		getJoystickSettings(joystick);
		
		// controls for the servo tube grabbers
		if(joy2Btn(1))
		{
			moveTubeServo(UP);
		}
		if(joy2Btn(2))
		{
			moveTubeServo(DOWN);
		}
	}
}

task main()
{
	initializeRobot();
	
	waitForStart();
	
	startTask(scoring);
	while (true)
	{
		getJoystickSettings(joystick);
		//TODO: add nudge controls

		if(abs(joystick.joy1_y2) >= 5)
		{
			if(joystick.joy1_y2 > 0)
				motor[RIGHT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y2);
			else
				motor[RIGHT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y2);
		}
		else
		{
			motor[RIGHT_DRIVE_MOTOR] = 0;
		}
		if(abs(joystick.joy1_y1) >= 5)
		{
			if(joystick.joy1_y1 > 0)
				motor[LEFT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y1);
			else
				motor[LEFT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y1);
		}
		else
		{
			motor[LEFT_DRIVE_MOTOR] = 0;
		}

		if(joy1Btn(6))
		{
			motor[RIGHT_SPINNER] = 100;
			motor[LEFT_SPINNER] = 100;
		}
		else if(joy1Btn(5))
		{
			motor[RIGHT_SPINNER] = -100;
			motor[LEFT_SPINNER] = -100;
		}
		else
		{
			motor[RIGHT_SPINNER] = 0;
			motor[LEFT_SPINNER] = 0;
		}
  }
}
