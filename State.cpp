#include "State.h"
#include "StateSnapshot.h"
#include <iostream>

/* Constructor of State object, Input is pwmController pointer*/
State::State(pwmController* p_pwmC) : pwmC(p_pwmC)
{
	setOne(getOneFromSensor() );
	setTwo(getTwoFromSensor() );
}


/* Definition of getOneFromSensor function of State
 * Uses ‘pwmC’ pwmController object to call getPin on first servo. Returns float between 0 and 1.
 */
float State::getOneFromSensor()
{
	return pwmC->getPin(0);
}

/* Definition of getTwoFromSensor function of State
 * Uses ‘pwmC’ pwmController object to call getPin on second servo. Returns float between 0 and 1.
 */
float State::getTwoFromSensor()
{
	return pwmC->getPin(1);
}


/* Definition of setOne function of State, Input of ‘pecentage’ float between 0 and 1
 * Uses ‘pwmC’ pwmController object to call pwmWritePercentage on first servo with float value
 */
void State::setOne(float p_one)
{
	//std::cout << "setOne" <<std::endl;
	this->One = p_one;
	pwmC->pwmWritePercentage(p_one,0);
}

/* Definition of setOne function of State, Input of ‘pecentage’ float between 0 and 1
 * Uses ‘pwmC’ pwmController object to call pwmWritePercentage on second servo with float value
 */
void State::setTwo(float p_two)
{
	//std::cout << "setTwo" <<std::endl;
	this->Two = p_two;
	pwmC->pwmWritePercentage(p_two,1);
}

/* Definition of createStateSnapshot function of State
 * Uses Statesnapshot constructor with inputs of state and two floats to return StateSnapshot
 * pointer
 */
StateSnapshot * State::createStateSnapshot()
{
	return new StateSnapshot(this, One, Two);
}
