#include "StateSnapshot.h"

/* Constructor of StateSnapshot object, Input is State pointer and two float values */
StateSnapshot::StateSnapshot(State * p_s,float p_one,float p_two): linkedState(p_s), currentOne(p_one), currentTwo(p_two)
{
}

/* Definition of restoreOne function of StateSnapshot
 * Uses ‘linkedState’ state to call setOne on ‘currentOne’ float value
 */
void StateSnapshot::restoreOne()
{
	this->linkedState->setOne(currentOne);	
}

/* Definition of restoreTwo function of StateSnapshot
 * Uses ‘linkedState’ state to call setTwo on ‘currentTwo’ float value
 */
void StateSnapshot::restoreTwo()
{
	this->linkedState->setTwo(currentTwo);
}

/* Definition of viewOne function of StateSnapshot
 * Uses ‘linkedState’ state to call getOneFromSensor to get float value to be returned
 */
float StateSnapshot::viewOne() {
	float currentOne = this->linkedState->getOneFromSensor();
	return currentOne;
}

/* Definition of viewTwo function of StateSnapshot
 * Uses ‘linkedState’ state to call getTwoFromSensor to get float value to be returned
 */
float StateSnapshot::viewTwo() {
	float currentTwo = this->linkedState->getTwoFromSensor();
	return currentTwo;
}
