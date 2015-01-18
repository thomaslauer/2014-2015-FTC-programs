#pragma once
#pragma systemFile

#include "hardwareDefinitions.h"

// movement directions
enum MoveDirections
{
	FORWARD, BACKWARD,
	RIGHT, LEFT,
	FORWARD_RIGHT, FORWARD_LEFT,
	BACKWARD_RIGHT, BACKWARD_LEFT,
	STOP
};

void stop()
{
	motor[RIGHT_DRIVE_MOTOR] = 0;
	motor[LEFT_DRIVE_MOTOR] = 0;
}

// method to move the robot in many directions
void move(MoveDirections direction, int speed)
{
	switch(direction)
	{
		case FORWARD:
			motor[RIGHT_DRIVE_MOTOR] 	= speed;
			motor[LEFT_DRIVE_MOTOR] 	= speed;
			break;
		case BACKWARD:
			motor[RIGHT_DRIVE_MOTOR] 	= -speed;
			motor[LEFT_DRIVE_MOTOR] 	= -speed;
			break;
		case RIGHT:
			motor[RIGHT_DRIVE_MOTOR] 	= speed;
			motor[LEFT_DRIVE_MOTOR] 	= -speed;
			break;
		case LEFT:
			motor[RIGHT_DRIVE_MOTOR] 	= -speed;
			motor[LEFT_DRIVE_MOTOR] 	= speed;
			break;
		case FORWARD_RIGHT:
			motor[RIGHT_DRIVE_MOTOR] 	= 0;
			motor[LEFT_DRIVE_MOTOR] 	= speed;
			break;
		case FORWARD_LEFT:
			motor[RIGHT_DRIVE_MOTOR] 	= speed;
			motor[LEFT_DRIVE_MOTOR] 	= 0;
			break;
		case BACKWARD_RIGHT:
			motor[RIGHT_DRIVE_MOTOR] 	= -speed;
			motor[LEFT_DRIVE_MOTOR] 	= 0;
			break;
		case BACKWARD_LEFT:
			motor[RIGHT_DRIVE_MOTOR] 	= 0;
			motor[LEFT_DRIVE_MOTOR] 	= -speed;
			break;
		default:
			stop();
	}
}

void move(MoveDirections direction, int speed, int duration)
{
	move(direction, speed);
	wait1Msec(duration);
	stop();
}

// positions for the tube servos
enum TubeServoPositions
{
	UP, DOWN
};

// method for moving the goal grabbing servos
void moveTubeServo(TubeServoPositions position)
{
	if(position == UP)
	{
		servo[LEFT_TUBE_SERVO] = LEFT_TUBE_UP;
		servo[RIGHT_TUBE_SERVO] = RIGHT_TUBE_UP;
	}
	if(position == DOWN)
	{
		servo[LEFT_TUBE_SERVO] = LEFT_TUBE_DOWN;
		servo[RIGHT_TUBE_SERVO] = RIGHT_TUBE_DOWN;
	}
}

void moveWinch(int power)
{
	motor[RIGHT_WINCH] = power;
	motor[LEFT_WINCH] = power;
}

void raiseWinch()
{
	moveWinch(50);
	wait1Msec(750);
	moveWinch(0);
}
