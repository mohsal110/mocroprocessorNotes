#include "MyBlinkLED.h"
#include "Utility.h"

void BlinkLED::Init()
{
	for (int i = 0; i < 8; i++)
		gpio.SetDirection(2, i, 1);
}

void BlinkLED::Run()
{
	while(true)
	{
		for (int i = 0; i < 8; i++)
		{
			gpio.Set(2, i);
			Utility::Delay(0x00fffff);
			gpio.Reset(2, i);
			Utility::Delay(0x00fffff);
		}
	}
}