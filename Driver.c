//FEEL FREE TO ASK QUESTIONS ABOUT PROGRAMMING!!!!11!ONE!1


#include "hardwareDefinitions.h"	//Lets the computer know about information about the robot, like wheel size
#include "motorControl.h"	//some tools for handleing the motors
#include "driverUtils.h"
#include "winchControl.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

const int nudgeSpeed = 25;	//sets the speed at which the nudge controls move the robot

void initializeRobot() //when the robot starts, this sets the servos/motors in the proper positions
{
	resetPositions();
  return;
}

task scoring()
{
	//puts the servos into their correct positions and raises the winch
	moveTubeServo(UP);
	servo[DUMP_SERVO] = DUMP_UP;

	resetWinchEncoder();	//tells the robot to count how far the motors turn

	while(true)
	{

		// start automatic winch control

		// home
		if(joy2Btn(BTN_A))	//if the A button is pressed, this moves the winch down.
		{
			startAutoWinch(convertDegreesToTicks(HOME * 360));
		}
		// 60cm goal
		if(joy2Btn(BTN_X))	//if the X button is pressed, this moves the winch to the 60cm goal position
		{
			startAutoWinch(convertDegreesToTicks(GOAL_60 * 360));
		}
		// 90cm goal
		if(joy2Btn(BTN_Y))	//if the Y button is pressed, this moves the winch to the 90cm goal position
		{
			startAutoWinch(convertDegreesToTicks(GOAL_90 * 360));
		}
		// 120cm goal
		if(joy2Btn(BTN_B))	//if the B button is pressed, this moves the winch to the 120cm goal position
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


		if(joystick.joy2_y1 >= 5 || joystick.joy2_y1 <= -5)//continues if the joystick is not in the middle
		{

			stopWinchControl();
			moveWinch(joystick.joy2_y1);//So if the joystick is moved, the winch will move up or down, depending on the direction the joystick is moved
		}
		else if(!isPIDActive) //if the joystick is in the center, tells the winch not to move.
		{

			moveWinch(0);
		}

		if(joy2Btn(BTN_START)) //if the start button is pressed,
		{
			stopWinchControl();	//stops the winch motor
			resetWinchEncoder();	//tells the computer that the winch is now lowered (this is for reset if computer gets off)
		}

		if(joy2Btn(BTN_LB)) //if the left back button is pressed,
		{
			servo[DUMP_SERVO] = DUMP_UP; //raises the dumper door
		}
		else if(joy2Btn(BTN_RB))	//if the right back button is pressed,
		{
			servo[DUMP_SERVO] = DUMP_DOWN;	//lowers the dumper door
		}

		// spinner controls
		if(joy2Btn(BTN_RT))	//if the top right button is pressed,
		{
			motor[SPINNER_MOTOR] = 75;	//spins the spinner inwards to suck in balls
		}
		else if(joy2Btn(BTN_LT))	//if the top left button is pressed,
		{
			motor[SPINNER_MOTOR] = -75;	//spins the spinner outwards to push balls away
		}
		else	//if no button is pressed
		{
			motor[SPINNER_MOTOR] = 0;	//tells the spinner not to move
		}
	}
}

task main()	//this is where the program actually starts!!!1!!ONE!!
{
	initializeRobot();	//starts the initialization (shown above)

	waitForStart();	//this waits until the referee is ready to start the match

	startTask(scoring);	//this starts that gigantic thing above

	bool rightDead = false;	//creates a variable to tell whether the robot is in deadzone or not
	bool leftDead = false;	//creates a variable to tell whether the robot is in deadzone or not
	while (true)
	{
		getJoystickSettings(joystick);
		alive();
		// drive controls and deadzone
		if(abs(joystick.joy1_y2) >= 5)	//if the right joystick is moved
		{
			rightDead = false;	//then the controler is not in deadzone
			if(joystick.joy1_y2 > 0)
				motor[RIGHT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y2);	//sets the motor power to the joystick reading
			else
				motor[RIGHT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y2);
		}
		else	//if the joysitck is in the deadzone
		{
			rightDead = true;	//sets the variable to true
		}
		if(abs(joystick.joy1_y1) >= 5)	//if the left joystick is moved
		{
			leftDead = false;	//then the controler is not in deadzone
			if(joystick.joy1_y1 > 0)
				motor[LEFT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y1);	//sets the motor power to the joystick reading
			else
				motor[LEFT_DRIVE_MOTOR] = exponentialDrive(joystick.joy1_y1);
		}
		else
		{
			leftDead = true;
		}

		// nudge controls

		if(rightDead && leftDead)	//if both of the joysticks are not moved, then go to nudge control
		{
			if(joystick.joy1_TopHat == -1)	//if the D-pad is not pressed, don't move motors
			{
				move(STOP, 0);
			}
			if(joystick.joy1_TopHat == 0)	//if the D-pad forward is pressed, move the robot forward at 25% power
			{
				move(FORWARD, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 1)	//if the D-pad is pressed to the upper right, move the robot forward turning right at 25% power
			{
				move(FORWARD_RIGHT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 2)	//if the D-pad is pressed right, rotate the robot to the right
			{
				move(RIGHT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 3) //if the D-pad is pressed backwards right, move the robot backards while turning right
			{
				move(BACKWARD_RIGHT, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 4)	//if the D-pad is pressed backwards, move the robot backwards
			{
				move(BACKWARD, nudgeSpeed);
			}
			if(joystick.joy1_TopHat == 5)	//okay I'm getting tired of typing and the rest of this is just the same in a counterclockwise circle
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



		if(joy1Btn(BTN_Y))	//if the Y button is pressed
		{
			servo[TUBE_SERVO] = TUBE_UP;	//moves the tube dump up
		}
		if(joy1Btn(BTN_B))	//if the B button is pressed
		{
			servo[TUBE_SERVO] = TUBE_DOWN;	//moves the tube dump down
		}
  }
}
