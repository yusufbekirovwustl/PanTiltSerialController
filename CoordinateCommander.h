#pragma once

#include <string>
#include <map>
#include "State.h"
#include "StateSnapshot.h"

/*Declaration of class CoordinateCommander */
class CoordinateCommander {
	public:
		CoordinateCommander(State * p_s,int p_serial_port);
		~CoordinateCommander() = default;
		int saveCoordinate(std::string s);
		int restoreCoordinate(std::string s);
		int viewSaved();
		int SetCoordinate(float f1,float f2);
		int SetRelCoordinate(float f1,float f2);
		int deleteSave(std::string s);
		void deliverMessage(std::string s);
	private:
		std::map<std::string, StateSnapshot*> snap;
		State * state;
		int serial_port;
};

//enum coordinateCommanderReturn;
