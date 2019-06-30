#include "GPIO.h"
#include "LPC17xx.h"

void GPIO::SetDirection(int port, int pin, int dir)

//FIODIR : Fast GPIO Port Direction control register. This register individually controls the direction of each port pin.
/*
FIO0DIR and FIO1DIR  :  Fast GPIO Direction PORTx control bits. Bit 0 in FIOxDIR
						controls pin Px.0, bit 31 in FIOxDIR controls pin Px.31.

for others : 0 Controlled pin is input.
			 1 Controlled pin is output.
						*/
	//reset value : 0x0


{
	if (port == 0)
	{
		LPC_GPIO0->FIODIR &= ~(1 << pin);//set the special bit to 0
		LPC_GPIO0->FIODIR |= dir << pin;//set the special bit to correct value
	}
	else if (port == 1)
	{
		LPC_GPIO1->FIODIR &= ~(1 << pin);
		LPC_GPIO1->FIODIR |= dir << pin;//it shifts dir for pin times to left
	}
	else if (port == 2)
	{
		LPC_GPIO2->FIODIR &= ~(1 << pin);
		LPC_GPIO2->FIODIR |= dir << pin;
	}
	else if (port == 3)
	{
		LPC_GPIO3->FIODIR &= ~(1 << pin);
		LPC_GPIO3->FIODIR |= dir << pin;
	}
	else if (port == 4)
	{
		LPC_GPIO4->FIODIR &= ~(1 << pin);
		LPC_GPIO4->FIODIR |= dir << pin;
	}
}

void GPIO::Set(int port, int pin)

/*FIO0SET		Fast GPIO output value Set bits. Bit 0 in FIOxSET controls pin
  FIO1SET		Px.0, bit 31 in FIOxSET controls pin Px.31.
  for others :  0 Controlled pin output is unchanged.
				1 Controlled pin output is set to HIGH.
  */

  //reset value : 0x0

  //Briefly , FIOSET is a register that set 1 to the pin of each port that we want

	/*	Access to a port pin via the FIOxSET register is conditioned by the corresponding bit of
		the FIOxMASK register
		A zero in this register’s bit enables an access to the corresponding physical pin via a read
		or write access. If a bit in this register is one, corresponding pin will not be changed with
		write access and if read, will not be reflected in the updated FIOxPIN register
		*/

{
	if (port == 0)
		LPC_GPIO0->FIOSET = 1 << pin;//it shifts 1 for pin times to left
	else if (port == 1)
		LPC_GPIO1->FIOSET = 1 << pin;
	else if (port == 2)
		LPC_GPIO2->FIOSET = 1 << pin;
	else if (port == 3)
		LPC_GPIO3->FIOSET = 1 << pin;
	else if (port == 4)
		LPC_GPIO4->FIOSET = 1 << pin;
}

void GPIO::Reset(int port, int pin)
{

	/*FIO0CLR		Fast GPIO output value Clear bits. Bit 0 in FIOxSET controls pin
	FIO1CLR		    Px.0, bit 31 in FIOxSET controls pin Px.31.
	for others :	0 Controlled pin output is unchanged.
				  	1 Controlled pin output is set to LOW.
	*/

	//reset value : 0x0

	//Briefly , FIOCLR is a register that set 0 to the pin of each port that we want

	if (port == 0)
		LPC_GPIO0->FIOCLR = 1 << pin;
	else if (port == 1)
		LPC_GPIO1->FIOCLR = 1 << pin;
	else if (port == 2)
		LPC_GPIO2->FIOCLR = 1 << pin;
	else if (port == 3)
		LPC_GPIO3->FIOCLR = 1 << pin;
	else if (port == 4)
		LPC_GPIO4->FIOCLR = 1 << pin;
}
/*  This register provides the value of port pins that are configured to perform only digital
	functions. The register will give the logic value of the pin regardless of whether the pin is
	configured for input or output, or as GPIO or an alternate digital function. As an example,
	a particular port pin may have GPIO input, GPIO output, UART receive, and PWM output
	as selectable functions. Any configuration of that pin will allow its current logic state to be
	read from the corresponding FIOxPIN register.
	*/

	/*FIO0PIN		Fast GPIO output value bits. Bit 0 corresponds to pin Px.0, bit 31
	  FIO1PIN		corresponds to pin Px.31. Only bits also set to 0 in the
					FIOxMASK register are affected by a write or show the pin’s
					actual logic state.
			    
	for others :	0    Reading a 0 indicates that the port pin’s current state is LOW.
					     Writing a 0 sets the output register value to LOW.
					1    Reading a 1 indicates that the port pin’s current state is HIGH.
					     Writing a 1 sets the output register value to HIGH.
	*/

	//Briefly , FIOPIN is a register that set value that we want to the pin of each port that we want

void GPIO::Toggle(int port, int pin)// result is not of the value of that oin
{
	if (port == 0)
		LPC_GPIO0->FIOPIN ^= 1 << pin;
	else if (port == 1)
		LPC_GPIO1->FIOPIN ^= 1 << pin;
	else if (port == 2)
		LPC_GPIO2->FIOPIN ^= 1 << pin;
	else if (port == 3)
		LPC_GPIO3->FIOPIN ^= 1 << pin;
	else if (port == 4)
		LPC_GPIO4->FIOPIN ^= 1 << pin;
}

void GPIO::SetValue(int port, int pin, bool value)
{
	if (port == 0)
	{
		LPC_GPIO0->FIOPIN &= ~(1 << pin);
		LPC_GPIO0->FIOPIN |= value << pin;
	}
	else if (port == 1)
	{
		LPC_GPIO1->FIOPIN &= ~(1 << pin);
		LPC_GPIO1->FIOPIN |= value << pin;//it shifts value for pin times to left and do bitwise OR
	}
	else if (port == 2)
	{
		LPC_GPIO2->FIOPIN &= ~(1 << pin);
		LPC_GPIO2->FIOPIN |= value << pin;
	}
	else if (port == 3)
	{
		LPC_GPIO3->FIOPIN &= ~(1 << pin);
		LPC_GPIO3->FIOPIN |= value << pin;
	}
	else if (port == 4)
	{
		LPC_GPIO4->FIOPIN &= ~(1 << pin);
		LPC_GPIO4->FIOPIN |= value << pin;
	}
}
