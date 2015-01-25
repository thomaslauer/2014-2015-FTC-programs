#pragma once
#pragma systemFile

#include "hardwareDefinitions.h"

int getNXTBattery()
{
	return nImmediateBatteryLevel;
}

int getExternalBattery()
{
	int value = externalBatteryAvg;
	return value;
}
