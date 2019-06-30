#include "lpc17xx.h"
#include "MyBlinkLED2.h"
#include "Utility.h"

void BlinkLED2::Init()
{
	LEDBlinkDir = true;
	//gpio.SetDirection(2, 12, 0);
	gpio.SetInterrupt(2, 12, BothEdge);
	for (int i = 0; i < 8; i++)
		gpio.SetDirection(2, i, 1);
}

void BlinkLED2::Run()
{
	while(true)
	{
//		if (gpio.getValue(2, 11) == false)
//			LEDBlinkDir = !LEDBlinkDir;
		
		if (LEDBlinkDir == true)
		{
			for (int i = 0; i < 8; i++)
			{
				gpio.Set(2, i);
				Utility::Delay(0x00fffff);
				gpio.Reset(2, i);
				Utility::Delay(0x00fffff);
			}
		}
		else
		{
			for (int i = 8; i >=0; i--)
			{
				gpio.Set(2, i);
				Utility::Delay(0x00fffff);
				gpio.Reset(2, i);
				Utility::Delay(0x00fffff);
			}
		}
				
	}
}


//IO0IntStatR : Interrupt Status for port 0 Rising Edge Interrupt
//Each bit in these read-only registers indicates the rising edge interrupt status for port 0.

//IO0IntStatF : Interrupt Status for port 0 Falling Edge Interrupt
//Each bit in these read-only registers indicates the falling edge interrupt status for port 0.

void BlinkLED2::InterruptHandler()
{
	if (LPC_GPIOINT->IO2IntStatF & (1 << 12))  //we want to find out what is 12's bit of this register ..If it is 1 ,the direction of leds change and if it is 0 do not change
			LEDBlinkDir = !LEDBlinkDir;
	if (LPC_GPIOINT->IO2IntStatR & (1 << 12))
			LEDBlinkDir = !LEDBlinkDir;
}