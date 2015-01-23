#pragma once
#pragma systemFile

#include "timer.h"

typedef struct
{
	int offset;
	tSensors port;
	float heading;
	Timer m_timer;
}Gyro;

void initGyro(Gyro& gyro, tSensors port)
{
	gyro.offset = 0;
	gyro.port = port;
	gyro.heading = 0;
	initTimer(gyro.m_timer, T2);
	resetTimer(gyro.m_timer);
}

void calibrateGyro(Gyro& gyro)
{
	long tempOffset = 0;

	int numOfTests = 50;
	for(int i = 0; i < numOfTests; i++)
	{
		tempOffset += SensorValue(gyro.port);
		wait1Msec(10);
	}
	tempOffset /= numOfTests;
	gyro.offset = tempOffset;
}

int readGyroRaw(Gyro& gyro)
{
	return SensorValue(gyro.port);
}

int readGyroSpeed(Gyro& gyro)
{
	return readGyroRaw(gyro) - gyro.offset;
}

void updateGyro(Gyro& gyro)
{
	float speed = (float)SensorValue(gyro.port) - gyro.offset;
	gyro.heading += speed * ((float)readTimer(gyro.m_timer) / 1000.0);
	resetTimer(gyro.m_timer);
}

void resetGyro(Gyro& g)
{
	g.heading = 0;
	resetTimer(g.m_timer);
}