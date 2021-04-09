#pragma once
#include "State.h"

class CoordinateCommander;  //foward declarations

/*Declaration of class StateSnapshot */
class StateSnapshot {
	public:
		StateSnapshot(State * p_s,float f1,float f2);
		~StateSnapshot() = default;
		void restoreOne();
		void restoreTwo();
		
	private:
		float currentOne;
		float currentTwo;
		State * linkedState;
		friend class CoordinateCommander;
		
	protected:
		float viewOne();
		float viewTwo();
};
