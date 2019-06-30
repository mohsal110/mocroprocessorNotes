#include "lpc17xx.h"
#include "MyBlinkLED.h"

BlinkLED leds;
int main (void) 
{
	SystemInit();
  leds.Init();
	leds.Run();
}

