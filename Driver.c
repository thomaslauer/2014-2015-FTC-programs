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

/*
 * The old scoring control software, which we have kept around for
 * future reference. After we finish the new scoring task,
 * we can delete this one.
 */

// task to run driver 2 stuff
//task scoring()
//{
//	moveTubeServo(UP);
//	servo[DUMP_SERVO] = DUMP_UP;
//
//	while(true)
//	{
//		getJoystickSettings(joystick);
//
//		// controls for the servo tube grabbers
//		if(joy2Btn(4))
//		{
//			moveTubeServo(UP);
//		}
//		if(joy2Btn(3))
//		{
//			moveTubeServo(DOWN);
//		}
//
//		if(joy2Btn(6))
//		{
//			moveWinch(100);
//		}
//		else if(joy2Btn(5))
//		{
//			moveWinch(-100);
//		}
//		else
//		{
//			moveWinch(0);
//		}
//
//		if(joy2Btn(1))
//		{
//			servo[DUMP_SERVO] = DUMP_UP;
//		}
//		else if(joy2Btn(2))
//		{
//			servo[DUMP_SERVO] = DUMP_DOWN;
//		}
//	}
//}



task scoring()
{
	// puts the servos into their correct positions
	moveTubeServo(UP);
	servo[DUMP_SERVO] = DUMP_UP;

	resetWinchEncoder();

	while(true)
	{
		if(joy2Btn(BTN_A))
		{
			startAutoWinch(convertDegreesToTicks(0 * 360));
		}
		if(joy2Btn(BTN_X))
		{
			startAutoWinch(convertDegreesToTicks(9 * 360));
		}
		if(joy2Btn(BTN_Y))
		{
			startAutoWinch(convertDegreesToTicks(13.5 * 360));
		}
		if(joy2Btn(BTN_B))
		{
			startAutoWinch(convertDegreesToTicks(18 * 360));
		}

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

		// spinner controls
		if(joy1Btn(5))
		{
			motor[SPINNER_MOTOR] = 75;
		}
		else if(joy1Btn(6))
		{
			motor[SPINNER_MOTOR] = -75;
		}
		else
		{
			motor[SPINNER_MOTOR] = 0;
		}

		if(joy1Btn(4))
		{
			moveTubeServo(UP);
		}
		if(joy1Btn(3))
		{
			moveTubeServo(DOWN);
		}
  }
}
