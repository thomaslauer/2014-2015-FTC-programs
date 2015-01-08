#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot()
{
  return;
}

task scoring()
{
	while(true)
	{
		getJoystickSettings(joystick);

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

		//TODO: add (small) deadzone
		//TODO: add exponential controls
		//TODO: add nudge controls

		if(abs(joystick.joy1_y2) >= 5)
		{
			motor[RIGHT_DRIVE_MOTOR] = joystick.joy1_y2;
		}
		else
		{
			motor[RIGHT_DRIVE_MOTOR] = 0;
		}

		if(abs(joystick.joy1_y1) >= 5)
		{
			motor[LEFT_DRIVE_MOTOR] = joystick.joy1_y1;
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
