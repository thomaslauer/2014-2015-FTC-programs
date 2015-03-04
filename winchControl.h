#pragma once
#pragma systemFile

#include "hardwareDefinitions.h"
#include "PID.h"

const float HOME = 0;
const float GOAL_60 = 9;
const float GOAL_90 = 13.5;
const float GOAL_120 = 18;

bool isPIDActive = false;
int winchPidTarget = 0;
PID winchPidController;

/*
 * The winch control task, which uses a PID controller to predict the best values
 * so we quickly get to the target and don't overshoot it
 */
task WinchTask()
{
	initPID(winchPidController, 0.05, 0, 2, winchPidTarget, T2);
	isPIDActive = true;
	while(isPIDActive)
	{
		int power = getPIDValue(winchPidController, nMotorEncoder[RIGHT_WINCH]);
		moveWinch(power);
		//playImmediateTone(440, 10);
	}
	moveWinch(0);
}

// stops the loop in the WinchTask
void stopWinchControl()
{
	isPIDActive = false;
}

// starts the auto winch control
void startAutoWinch(int target)
{
	stopWinchControl();
	winchPidTarget = target;
	startTask(WinchTask);
}

//used to convert user input into someting the PID controler can use
int convertDegreesToTicks(int degrees)
{
	return ((float)degrees/360.0) * 1440.0;
}

void resetWinchEncoder()
{
	nMotorEncoder[RIGHT_WINCH] = 0;
}
