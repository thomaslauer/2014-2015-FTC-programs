#include "battery.h"

task main()
{

  while(true){
  		displayCenteredTextLine(1, "BATTERY TESTER");
  		displayTextLine(3, "NXT: %1.3f", (float)getNXTBattery()/1000.0);
  		displayTextLine(4, "EXT: %2.2f", (float)getExternalBattery()/1000.0);
  	}
}
