#include "uart.h"
#include "lpc17xx.h"

void UART::Connect(int uartNo)
{
	if (uartNo == 2)
	{
		//LPC_PINCON->PINSEL0 &= ~(15 << 20);
		LPC_PINCON->PINSEL0 |= 1 << 20; //txd2
		LPC_PINCON->PINSEL0 |= 1 << 22;	//rxd2
	}
}
/*	DLM (DLAB =1) : Divisor Latch MSB. Most significant byte of the baud
	rate divisor value. The full divisor is used to generate a
	baud rate from the fractional rate divider...R/W
*/


/*	DLL (DLAB =1) : Divisor Latch LSB. Least significant byte of the baud
	rate divisor value. The full divisor is used to generate a
	baud rate from the fractional rate divider...R/W
	*/

/*	FDR : Fractional Divider Register. Generates a clock input for
	the baud rate divider...R/W
	*/

/*	THR (DLAB =0) : Transmit Holding Register. The next character to be
	transmitted is written here...WO
	*/

/*	RBR (DLAB =0) : Receiver Buffer Register. Contains the next received
	character to be read...RO
	*/
void UART::Init(int uartNo, DataLength dlen, StopBit sb, Parity p, int Buadrate)
{
	//LCR : Line Control Register. Contains controls for frame formatting and break generation...R/W
	Connect(uartNo);
	if (uartNo == 2)
	{
		LPC_UART2->LCR = dlen;
		LPC_UART2->LCR |= sb << 2;
		if (p != Parity_Non)
		{
			LPC_UART2->LCR |= 1 << 3;
			LPC_UART2->LCR |= p << 4;
		}	
	}
	
	SetBaudRate(uartNo, Buadrate);
}

extern uint32_t SystemFrequency;
void UART::SetBaudRate(char UartNum, int Baudrate)
{
	unsigned int uClk = SystemFrequency >> 2;
	unsigned int d, m, bestd, bestm, tmp;
	uint64_t best_divisor, divisor;
	unsigned int current_error, best_error;
	unsigned int recalcbaud;
	best_error = 0xFFFFFFFF; /* Worst case */
	bestd = 0;
	bestm = 0;
	best_divisor = 0;
	for (m = 1 ; m <= 15 ;m++)
	{
		for (d = 0 ; d < m ; d++)
		{
			divisor = ((uint64_t)uClk * 268435456)*m / (Baudrate*(m+d));
			current_error = divisor & 0xFFFFFFFF;

			tmp = divisor / 4294967296;

			/* Adjust error */
			if(current_error > ((unsigned int)0x80000000))
			{
				current_error = -current_error;
				tmp++;
			}

			/* Out of range */
			if(tmp < 1 || tmp > 65536)
				continue;

			if( current_error < best_error)
			{
				best_error = current_error;
				best_divisor = tmp;
				bestd = d;
				bestm = m;
				
				if(best_error == 0) 
					break;
			}
		} /* end of inner for loop */

		if (best_error == 0)
			break;
	} /* end of outer for loop  */
	recalcbaud = (uClk >> 4) * bestm / (best_divisor * (bestm + bestd));
	/* reuse best_error to evaluate baud error*/
	if(Baudrate > recalcbaud) 
		best_error = Baudrate - recalcbaud;
	else 
		best_error = recalcbaud -Baudrate;
	best_error = best_error * 100 / Baudrate;
 	if (best_error < 3)
	{
		if (UartNum == 2)
		{
			LPC_UART2->LCR |= 0x80;
			LPC_UART2->DLM = (best_divisor >> 8) & 0xFF;
			LPC_UART2->DLL = best_divisor & 0xFF;
			/* Then reset DLAB bit */
			LPC_UART2->LCR &= ~0x80;
			LPC_UART2->FDR = ((bestm << 4) & 0xF0)
								| (bestd & 0x0F);
		}
	}
}

void UART::Send(unsigned char d)
{
	while (!(LPC_UART2->LSR & (1 << 5)));
	LPC_UART2->THR = d;
}

unsigned char UART::Get()
{
	while (!(LPC_UART2->LSR & 1));
	return LPC_UART2->RBR ;
}