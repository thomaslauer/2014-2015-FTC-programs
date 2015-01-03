#pragma once
#pragma systemFile

#include "timer.h"

typedef struct
{
	float kp;
	float ki;
	float kd;
	float lastError;
	float integral;
	float derivative;
	float target;
	Timer timer;
}PID;

void initPID(PID &pid, float kp, float ki, float kd, float target, TTimers timer)
{
	pid.kp = kp;
	pid.ki = ki;
	pid.kd = kd;
	pid.lastError = 0;
	pid.integral = 0;
	pid.derivative = 0;
	pid.target = target;
	initTimer(pid.timer, timer);
}

void initPID(PID &pid, float kp, float ki, float kd, TTimers timer)
{
	pid.kp = kp;
	pid.ki = ki;
	pid.kd = kd;
	pid.lastError = 0;
	pid.integral = 0;
	pid.derivative = 0;
	pid.target = 0;
	initTimer(pid.timer, timer);
}

void setPIDTarget(PID &pid, float target)
{
	pid.target = target;
}

void clearPID(PID &pid)
{
	initPID(pid, pid.kp, pid.ki, pid.kd, 0.0, pid.timer.hardwareTimer);
}

float getPIDValue(float input, PID &pid)
{
	float currentError = pid.target - input;
	int deltaTime = getTimerValue(pid.timer);
	pid.integral += currentError * (deltaTime) / 1000;
	pid.derivative = (currentError - (pid.lastError))/((float)(deltaTime));
	pid.lastError = currentError;
	resetTimer(pid.timer);
	float pidValue = (pid.kp) * currentError + (pid.ki) * (pid.integral) + (pid.kd) * (pid.derivative);
	return pidValue;
}
