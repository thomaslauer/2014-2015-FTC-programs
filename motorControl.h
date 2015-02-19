#pragma once
#pragma systemFile

#include "hardwareDefinitions.h"

#include "gyro.h"
#include "PID.h"

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
			motor[RIGHT_DRIVE_MOTOR] 	= -speed;
			motor[LEFT_DRIVE_MOTOR] 	= speed;
			break;
		case LEFT:
			motor[RIGHT_DRIVE_MOTOR] 	= speed;
			motor[LEFT_DRIVE_MOTOR] 	= -speed;
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
	UP, DOWN, STORE
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
	if(position == STORE)
	{
		servo[LEFT_TUBE_SERVO] = LEFT_TUBE_STORED;
		servo[RIGHT_TUBE_SERVO] = RIGHT_TUBE_STORED;
	}
}

void moveWinch(int power)
{
	motor[RIGHT_WINCH] = power;
	motor[LEFT_WINCH] = power;
}

void moveWinch(int power, int time)
{
	motor[RIGHT_WINCH] = power;
	motor[LEFT_WINCH] = power;
	wait1Msec(time);
	moveWinch(0);
}

void raiseWinch()
{
	moveWinch(50);
	wait1Msec(750);
	moveWinch(0);
}


/*
removed the old gyroTurn method, because it didn't work
*/

/*
void gyroTurn(Gyro &g, PID &p, int angle, int speed)
{
initPID(p, 1, 0.0000001, 1, T2);
setPIDTarget(p, angle);
g.heading = 0;
while(true)
{
float currentPidValue = getPIDValue(p, g.heading);
//displayTextLine(1, "heading: %d", g.heading);
//displayTextLine(2, "PID error: %d", p.lastError);
//displayTextLine(3, "value: %d", currentPidValue);
move(RIGHT, currentPidValue);
updateGyro(g);
}
}
*/


void gyroTurn(Gyro &g, int angle, int power)
{
	const float returningSpeed = 0.5;

	resetGyro(g);

	angle = angle * -1;

	if (angle > 0)
	{
		motor[RIGHT_DRIVE_MOTOR] = power;
		motor[LEFT_DRIVE_MOTOR] = -power;
		//motor[LEFT_DRIVE_MOTOR] = 0;
		float gyroVal = 0;
		bool running = true;
		bool returning = false;
		while (running) {
			updateGyro(g);

			if (abs(g.heading) > abs(angle)){
				returning = true;
				//playImmediateTone(440, 100);
			}
			if (returning){
				motor[RIGHT_DRIVE_MOTOR] = -((float)power * returningSpeed);
				//motor[RIGHT_DRIVE_MOTOR] = 0;
				motor[LEFT_DRIVE_MOTOR] = ((float)power * returningSpeed);
				if (abs(g.heading) < abs(angle)){
					running = false;
					writeDebugStreamLine("Final GyroVal: %f", gyroVal);
				}
			}

			wait1Msec(5);
		}
	}
	else if (angle < 0)
	{
		motor[RIGHT_DRIVE_MOTOR] = -power;
		//motor[RIGHT_DRIVE_MOTOR] = 0;
		motor[LEFT_DRIVE_MOTOR] = power;
		float gyroVal = 0;
		bool running = true;
		bool returning = false;
		while (running) {
			updateGyro(g);

			if (abs(g.heading) > abs(angle)){
				returning = true;
				//playImmediateTone(440, 100);
			}
			if (returning){
				motor[RIGHT_DRIVE_MOTOR] = ((float)power * returningSpeed);
				motor[LEFT_DRIVE_MOTOR] = -((float)power * returningSpeed);
				//motor[LEFT_DRIVE_MOTOR] = 0;
				if (abs(g.heading) < abs(angle)){
					running = false;
					writeDebugStreamLine("Final GyroVal: %f", gyroVal);
				}
			}

			wait1Msec(5);
		}
	}
	move(STOP, 0);
	resetGyro(g);
}
