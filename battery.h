#pragma once
#pragma systemFile

#include "hardwareDefinitions.h"

int getNXTBattery()
{
	return nImmediateBatteryLevel;
}

int getExternalBattery()
{
	return externalBatteryAvg;
}

const int NXTLow = 8000;
const int ExtLow = 14000;

void batteryError()
{
	if (getNXTBattery() < NXTLow)
	{
		// play error tone and display error
	}
	if (getExternalBattery() < ExtLow)
	{
		// play error tone and display error
	}
}