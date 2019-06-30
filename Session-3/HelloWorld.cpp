#include "HelloWorld.h"
#include "UART.h"

UART uart;

void HelloWorld::Init()
{
	uart.Init(2, Data_8Bits, Stop_1Bit, Parity_Non, 115200);
}