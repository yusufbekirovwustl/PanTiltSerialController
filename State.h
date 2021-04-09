#pragma once
#include "pwmController.h"

class StateSnapshot; //foward declaration

/*Declaration of class StateSnapshot */
class State {
	public:
		State(pwmController * p_pwmC);
		~State() = default;
		StateSnapshot * createStateSnapshot();
		
	private:
		float One;
		float Two;
		float getOneFromSensor();
		float getTwoFromSensor();
		pwmController * pwmC;
		friend class StateSnapshot;
		
	protected:
		void setOne(float f);
		void setTwo(float f);
};
