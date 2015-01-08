#pragma once
#pragma systemFile

enum ColorModes
{
	MODE_RED,
	MODE_GREEN,
	MODE_BLUE,
	MODE_FULL,
	MODE_NONE
};

enum ColorCodes
{
	BLACK 	= 1,
	BLUE 		= 2,
	GREEN 	= 3,
	YELLOW 	= 4,
	RED			= 5,
	WHITE 	= 6
};

typedef struct
{
	tSensors port;
	ColorModes color;


}ColorSensor;

void setColorSensorMode(ColorSensor &c, ColorModes color)
{
	c.color = color;
	//SensorType[S3] = sensorColorNxtFULL;

	switch(color)
	{
		case MODE_RED: 		SensorType[c.port] = sensorColorNxtRED; 		break;
		case MODE_GREEN:	SensorType[c.port] = sensorColorNxtGREEN; 	break;
		case MODE_BLUE: 	SensorType[c.port] = sensorColorNxtBLUE; 		break;
		case MODE_FULL: 	SensorType[c.port] = sensorColorNxtFULL; 		break;
		case MODE_NONE: 	SensorType[c.port] = sensorColorNxtNONE; 		break;
		default:					SensorType[c.port] = sensorColorNxtFULL;
	}


}

void initColor(ColorSensor &c, ColorModes color, tSensors colorPort)
{
	c.port = colorPort;
	setColorSensorMode(c, color);
}
