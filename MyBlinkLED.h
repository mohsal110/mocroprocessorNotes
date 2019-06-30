#include "GPIO.h"
class BlinkLED
{
	public:
		void Init();
		void Run();
	
	private:
		GPIO gpio;
};