#pragma once
#pragma systemFile

#include "timer.h"

typedef struct
{
	int offset;
	tSensors port;
}Gyro;

void initGyro(Gyro& gyro, tSensors port)
{
	gyro.offset = 0;
	gyro.port = port;
}

void calibrateGyro(Gyro& gyro)
{
	long tempOffset = 0;

	int numOfTests = 50;
	for(int i = 0; i < numOfTests; i++)
	{
		tempOffset += SensorValue(gyro.port);
	}
	tempOffset /= numOfTests;
	gyro.offset = tempOffset;
}
