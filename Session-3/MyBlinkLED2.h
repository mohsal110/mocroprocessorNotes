#include "GPIO.h"
class BlinkLED2
{
	public:
		void Init();
		void Run();
		void InterruptHandler();
		bool LEDBlinkDir;
	
	private:
		GPIO gpio;
};