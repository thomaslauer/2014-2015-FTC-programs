#define NO_JOYSTICK

#include "hardwareDefinitions.h"
#include "motorControl.h"

task main()
{
	while(true)
	{
		SensorMode[ULTRASONIC_PORT] = sensorSONAR;
		displayTextLine(3, "Value: %d", SensorValue[ULTRASONIC_PORT]);
	}
}
