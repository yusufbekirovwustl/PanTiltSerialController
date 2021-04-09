#include <wiringPi.h>
#include <wiringSerial.h>
#include "pwmController.h"
#include "pca9685.h"

#include <iostream>

#define MAX_PWM 4096

/* Constructor of pwmCOntroller object, Input is base of i2c as int, hertz as int, and also
 * minimumm and maximum millis values for both servos
 */
pwmController::pwmController(int p_pin_base, int p_hertz, float p_minMillis, float p_maxMillis, float p_minMillisTwo, float p_maxMillisTwo) : pin_base(p_pin_base), hertz(p_hertz), minMillis(p_minMillis) , maxMillis(p_maxMillis), minMillisTwo(p_minMillisTwo) , maxMillisTwo(p_maxMillisTwo)
{
}

/* Definition of calcTicks function of pwmController, Input is impulseMs as float and hertz as int
 * Returns number of ticks required to be high to use pwmWrite function in wiringPi
 */
int pwmController::calcTicks(float impulseMs, int hertz)
{
	float cycleMs = 1000.0f / hertz; 
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}


/* Definition of calcMillis function of pwmController, Input is ticks as int and hertz as int
 * returns number of millis in inputed number of ticks
 */
float calcMillis(int ticks, int hertz)
{
    return (ticks * ((1000.0f/hertz) + 0.5f)) / MAX_PWM;
}

/* Definition of map function of pwmController Input is float input 0-1, and a min and max float
 * Calculates float value between min and max corresponding to input percentage
 * output is float min-max
 */
float pwmController::map(float input, float min, float max)
{
	if(input>=0 && input<= 1)
	{
		return (input * max) + (1 - input) * min;
	}
	else if(input<0)
	{
		return min;
	}
	else
	{
		return max;
	}
}

/* Definition of unmap function of pwmController. Input is float input min-max, and a min and max float
 * Calculates float value between 0 and 1 corresponding to input position
 * output is float 0-1
 */
float pwmController::unmap(float input, float min, float max)
{
	std::cout << "Input:" << input << std::endl;
	if(input>=min && input<= max)
	{
		return (input-min)/(maxMillis-min);
	}
	else if(input<min)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/* Definition of pwmWritePercentage function of pwmController. Input is float input 0-1,
 * and a pin input int 0 or 1. Calculates millis and ticks to call pwmWrite of wiringPi
 */
void pwmController::pwmWritePercentage(float input, int pin) 
{
	//std::cout << "pwmWritePercentage, Pin: " << pin << " Input: " << input <<std::endl;
	
	float min = minMillis;
	float max = maxMillis; 
	if(pin == 0)
	{
		//std::cout << "Using Two in Write:" << std::endl;
		min = minMillisTwo;
		max = maxMillisTwo;
	}
	
	
	float millis = map(input, min, max);
	std::cout << "Millis read: " << millis << "With min: " << min << "With Max: " << max << "\n" << std::endl;
	int tick = calcTicks(millis, hertz);
	pwmWrite(pin_base+pin, tick);
	std::cout << "Done " <<std::endl;
}

/* Definition of getPin function of pwmController. Input is int pinNo 0 or 1,
 * Calculates current millis of requested servo in pinNo, converts to millis float value and
 * converted to value between 0-1 based on current min/max value for the specified servo
 */
float pwmController::getPin(int pinNo)
{
	float min = minMillis;
	float max = maxMillis;
	if(pinNo == 0)
	{
		min = minMillisTwo;
		max = maxMillisTwo;
	}
	
	int millisint = digitalRead(pin_base+pinNo);
	float millis = calcMillis(millisint, hertz);
	return unmap(millis, min, max);
	
}

