#include "motorControl.h"

task main()
{
	servo[DUMP_SERVO] = DUMP_UP;
	wait1Msec(500);
	moveWinch(10);

  while (true)
  {}
}
