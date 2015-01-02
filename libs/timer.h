#pragma once
#pragma systemFile

/**
 * Timer struct holds information on the timer
 * It currently has a reference to the hardware timer,
 * the staritng time, and the target time
 */
typedef struct
{
	TTimers hardwareTimer;
	int startTime;
	int targetTime;
}Timer;

/**
 * Sets up the variables in a timer
 */
void initTimer(Timer& timer, TTimers hardwareTimer)
{
	timer.hardwareTimer = hardwareTimer;
	timer.startTime = 0;
	timer.targetTime = 0;
}

/**
 * Resets the timer, changing the startTime to the current
 * hardware time.
 */
void resetTimer(Timer& timer)
{
	timer.startTime = time1[timer.hardwareTimer];
}

/**
 * gets how long the timer has been running
 */
int readTimer(Timer& timer)
{
	return time1[timer.hardwareTimer] - timer.startTime;
}

/**
 * sets the target for the timer
 */
void setTimerTarget(Timer& timer, int target)
{
	timer.targetTime = target;
}
