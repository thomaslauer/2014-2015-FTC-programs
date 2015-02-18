/*

Hardware definitions file!

This defines where all our sensors, motors, servos, and electronics are connected.

TO USE:
	~ remove all the #pragmas from the program
	~ add [include "hardwareDefinitions.h"]
	~ compile the program to bring in all the constants


TO ADD AN ENTRY:
	motor:
		const tMotor <MOTOR NAME> = <MOTOR PORT>;
		example: const tMotor RIGHT_DRIVE_MOTOR = motorD;
	servo:
		const TServoIndex <SERVO NAME> = <SERVO PORT>;
		example: const TServoIndex DUMP_SERVO = servo1;
	servo position:
		const int <SERVO NAME><POSITION NAME> = <POSITION>;
		example: const int DUMP_UP = 100;
	sensor:
		const tSensors <SENSOR NAME = <SENSOR PORT>;
		example: const tSensors GYRO = S2;

	In general, try to keep the names in CAPS to show that they are constants.
	Try to have all the '=' line up across the page, it makes it look neat.
	COMMENT TO SHOW WHAT THE CONSTANTS ARE FOR
*/

#pragma once
#pragma systemFile


// standard pragmas. we don't name anything with the pragmas, but instead use constants below.
// this lets us give motors multiple names, and we get more flexability in naming things.
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

// drive motor definitions
const tMotor RIGHT_DRIVE_MOTOR			= motorD;
const tMotor LEFT_DRIVE_MOTOR 			= motorE;

const tMotor RIGHT_WINCH 						= motorF;
const tMotor LEFT_WINCH 						= motorG;

// spinner motors
const tMotor SPINNER_MOTOR 					= motorH;

// the dumper servo on the schlorp tube
const TServoIndex DUMP_SERVO 				= servo1;
const int DUMP_UP 									= 245;
const int DUMP_DOWN 								= 60;

// right servo for grabbing tubes
const TServoIndex RIGHT_TUBE_SERVO 	= servo2;
const int RIGHT_TUBE_UP 						= 127;
const int RIGHT_TUBE_DOWN 					= 5;

// left servo for grabbing tubes
const TServoIndex LEFT_TUBE_SERVO 	= servo3;
const int LEFT_TUBE_UP 							= 127;
const int LEFT_TUBE_DOWN 						= 250;

// port for the gyro sensor
const tSensors GYRO_PORT 						= S2;

//port for IR sensor
const tSensors IR_PORT 							= S3;

// resets the positions of all the servos
void resetPositions()
{
	servo[DUMP_SERVO] 								= DUMP_UP;
	servo[RIGHT_TUBE_SERVO] 					= RIGHT_TUBE_DOWN;
	servo[LEFT_TUBE_SERVO] 						= LEFT_TUBE_DOWN;
}
