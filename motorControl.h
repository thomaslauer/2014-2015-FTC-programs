#pragma once
#pragma systemFile

void move(int power)
{
	motor[motorD] = power;
	motor[motorE] = power;
}

void turn(int power)
{
	motor[motorD] = power;
	motor[motorE] = -power;
}
