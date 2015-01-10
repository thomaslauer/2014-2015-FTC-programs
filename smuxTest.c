#include "hardwareDefinitions.h"
#include "hitechnic-sensormux.h"
#include "lego-touch.h"

tMUXSensor touch = msensor_S4_1;

task main
{
	SensorType[S4] = sensorI2CCustom;
	while(true)
	{
		if(TSReadState(touch))
		{
			displayTextLine(3, "Pressed");
		}
		else
		{
			displayTextLine(3, "Released");
		}
	}
}
