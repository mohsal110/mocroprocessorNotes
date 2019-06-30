class GPIO
{
	public:
		void SetDirection(int port, int pin, int dir);
		void Set(int port, int pin);
		void Reset(int port, int pin);
		void Toggle(int port, int pin);
		void SetValue(int port, int pin, bool value);
};