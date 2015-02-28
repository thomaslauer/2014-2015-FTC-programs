#pragma once
#pragma systemFile

#include "hardwareDefinitions.h"
#include "PID.h"

bool isPIDActive = false;
int winchPidTarget = 0;
PID winchPidController;

task WinchTask()
{
	initPID(winchPidController, 0.05, 0, 2, winchPidTarget, T2);
	isPIDActive = true;
	while(isPIDActive)
	{
		int power = getPIDValue(winchPidController, nMotorEncoder[RIGHT_WINCH]);
		moveWinch(power);
	}
	moveWinch(0);
}


// starts the auto winch control
void startAutoWinch(int target)
{
	winchPidTarget = target;
	startTask(WinchTask);
}

// stops the loop in the WinchTask
void stopWinchControl()
{
	isPIDActive = false;
}
