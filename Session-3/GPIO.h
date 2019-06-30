#ifndef GPIO_H
#define GPIO_H

#include "lpc17xx.h"

enum Edge 
{
	FallingEdge = 0,
	RisingEdge = 1,
	BothEdge = 2
};

class GPIO
{
	public:
		GPIO();
		void SetDirection(int port, int pin, int dir);
		void SetInterrupt(int port, int pin, Edge edge);
		void Set(int port, int pin);
		void Reset(int port, int pin);
		void Toggle(int port, int pin);
		void SetValue(int port, int pin, bool value);
		bool getValue(int port, int pin);
	
		LPC_GPIO_TypeDef* GPIOs[5];
};

#endif