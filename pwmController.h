#pragma once

/*Declaration of class pwmCOntroller*/
class pwmController{
	public:
		pwmController(int pin_base, int hertz, float minMillis, float maxMillis, float minMillisTwo, float maxMillisTwo);
		void pwmWritePercentage(float input, int pin);
		float getPin(int pinNo);
		
	private:
		int pin_base;
		int hertz;
		float minMillis;
		float maxMillis;
		
		float minMillisTwo;
		float maxMillisTwo;
	protected:
		int calcTicks(float impulse, int hz);
		float map(float input,float min, float max);
		float unmap(float input,float min, float max);
};


