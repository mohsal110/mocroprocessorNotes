#ifndef UART_H
#define UART_H

enum DataLength
{
	Data_5Bits,
	Data_6Bits,
	Data_7Bits,
	Data_8Bits
};

enum StopBit
{
	Stop_1Bit,
	Stop_2Bit
};

enum Parity
{
	Parity_Odd,
	Parity_Even,
	Parity_Non = 10
};

class UART
{
	public:
		void Init(int uartNo, DataLength dlen, StopBit sb, Parity p, int Buadrate);
		void Connect(int uartNo);
		void SetBaudRate(char UartNum, int Baudrate);
		void Send(unsigned char d);
		unsigned char Get();
};

#endif