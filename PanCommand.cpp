
#include "PanCommand.h"
enum panReturn { panSuccess, panCommandFail};

using namespace std;

/* Constructor of PanCommand object*/
PanCommand::PanCommand(CoordinateCommander* p_cc) : cc(p_cc) //Constructor
{
}

/* Definition of execute function of PanCommand, Input is string arguement
 * If arguement is correct, calls SetRelCoordinate function of CoordinateCommander and returns
 * panSuccess, otherwise calls displayInfo function and returns panCommandFail.
 */
int PanCommand::execute(std::string s)
{
	if(s == "left") 
	{	
		if(!(this->cc->SetRelCoordinate(0,-.1)))
		{
			return panSuccess;
		}	
	}
	else if(s == "right")
	{
		if(!this->cc->SetRelCoordinate(0,.1))
		{
			return panSuccess;
		}
		
	}
	else if(s == "up")
	{
		if(!this->cc->SetRelCoordinate(.1,0))
		{
			return panSuccess;
		}
		
	}
	else if(s == "down")
	{
		if(!this->cc->SetRelCoordinate(-.1,0))
		{
			return panSuccess;
		}	
	}
	displayInfo();
	return panCommandFail;

}

/* Delivers message to Serial PC User using CoordinateCommander */
void PanCommand::displayInfo() 
{
	cc->deliverMessage("Enter 'pan [direction]' where [direction] = 'left', 'right', 'up', or 'down' \n");
}
