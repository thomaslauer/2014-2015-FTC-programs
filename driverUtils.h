#pragma once
#pragma systemFile

const int DeadZone = 5;
const int MinimumPower = 10;
const float ExponentialControl = 2;

int exponentialDrive(int joyValue, float driveExp, int dead, int minimum)
{
	int joyMax = 128 - dead;
	int joySign = sgn(joyValue);
	int joyLive = abs(joyValue) - dead;
	return joySign * (minimum + ((100 - minimum) * pow(joyLive, driveExp) / pow(joyMax, driveExp)));
}

int exponentialDrive(int joyValue)
{
	return exponentialDrive(joyValue, ExponentialControl, DeadZone, MinimumPower);
}
