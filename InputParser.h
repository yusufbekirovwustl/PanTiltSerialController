#pragma once
#include "AbstractCommand.h"
#include <map>

/* Class Declaration for InputParser */
class InputParser
{
	public:
		InputParser(int p_serial_port);
		~InputParser() = default;
		int addCommand(std::string s,AbstractCommand* ac); 
		int run();
		
	
	private:
		int serial_port;
		std::map<std::string, AbstractCommand*> m;
		
	protected:
		void listCommands();
		std::string prompt();
};

