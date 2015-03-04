#include "hardwareDefinitions.h"
#include "motorControl.h"
#include "driverUtils.h"
#include "winchControl.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

const int nudgeSpeed = 25;

void initializeRobot()
{
	resetPositions();
  return;
}

task scoring()
{
	// puts the servos into their correct positions
	moveTubeServo(UP);
	servo[DUMP_SERVO] = DUMP_UP;

	resetWinchEncoder();

	while(true)
	{

		// start automatic winch control

		// home
		if(joy2Btn(BTN_A))
		{
			startAutoWinch(convertDegreesToTicks(HOME * 360));
		}
		// 60cm goal
		if(joy2Btn(BTN_X))
		{
			startAutoWinch(convertDegreesToTicks(GOAL_60 * 360));
		}
		// 90cm goal
		if(joy2Btn(BTN_Y))
		{
			startAutoWinch(convertDegreesToTicks(GOAL_90 * 360));
		}
		// 120cm goal
		if(joy2Btn(BTN_B))
		{
			startAutoWinch(convertDegreesToTicks(GOAL_120 * 360));
		}
		// end automatic winch control

		// START old button winch control
		/*
		if(joy2Btn(BTN_LB))
		{
			stopWinchControl();
			moveWinch(-100);
		}
		else if(joy2Btn(BTN_RB))
		{
			stopWinchControl();
			moveWinch(100);
		}
		else
		{
			if(!isPIDActive)
			{
				moveWinch(0);
			}
		}
		*/
		// END old button winch control


		if(joystick.joy2_y1 >= 5 || joystick.joy2_y1 <= -5)
		{

			stopWinchControl();
			moveWinch(joystick.joy2_y1);
		}
		else if(!isPIDActive)
		{

			moveWinch(0);
		}

		if(joy2Btn(BTN_START))
		{
			stopWinchControl();
			resetWinchEncoder();
		}

		if(joy2Btn(BTN_LB))
		{
			servo[DUMP_SERVO] = DUMP_UP;
		}
		else if(joy2Btn(BTN_RB))
		{
			servo[DUMP_SERVO] = DUMP_DOWN;
		}

		// spinner controls
		if(joy2Btn(BTN_LT))
		{
			motor[SPINNER_MOTOR] = 75;
		}
		else if(joy2Btn(BTN_RT))
		{
			motor[SPINNER_MOTOR] = -75;
		}
		else
		{
			motor[SPINNER_MOTOR] = 0;
		}
	}
}

task main()
{
	initializeRobot();

	waitForStart();

	startTask(scoring);

	bool rightDead = false;
	bool leftDead = false;
	while (true)
	{
		getJoystickSettings(joystick);
		//TODO: add nudge controls
		alive();
		// drive controls and deadzone
		if(abs(joystick.joy1_y2) >= 5)
		{
			rightDead = false;
			if(joystick.joy1_y2 > 0)
				motor[RIGHT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y2);
			else
				motor[RIGHT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y2);
		}
		else
		{
			rightDead = true;
		}
		if(abs(joystick.joy1_y1) >= 5)
		{
			leftDead = false;
			if(joystick.joy1_y1 > 0)
				motor[LEFT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y1);
			else
				motor[LEFT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y1);
		}
		else
		{
			leftDead = true;
		}

		// nudge controls

		if(rightDead && leftDead)
		{
			if(joystick.joy1_TopHat == -1)
			{
				move(STOP, 0);
			}
			if(joystick.joy1_TopHat == 0)
			{
				move(FORWARD, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 1)
			{
				move(FORWARD_RIGHT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 2)
			{
				move(RIGHT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 3)
			{
				move(BACKWARD_RIGHT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 4)
			{
				move(BACKWARD, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 5)
			{
				move(BACKWARD_LEFT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 6)
			{
				move(LEFT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 7)
			{
				move(FORWARD_LEFT, nudgeSpeed);
			}
		}



		if(joy1Btn(BTN_Y))
		{
			servo[TUBE_SERVO] = TUBE_UP;
		}
		if(joy1Btn(BTN_B))
		{
			servo[TUBE_SERVO] = TUBE_DOWN;
		}
  }
}
