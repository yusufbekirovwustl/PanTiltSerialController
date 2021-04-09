
#include "SetCommand.h"
#include <sstream>

enum setReturn { setSuccess, setCommandFail};

using namespace std;

/* Constructor of SetCommand object, Input is pointer to CoordinateCommander object */
SetCommand::SetCommand(CoordinateCommander* p_cc) : cc(p_cc) //Constructor
{
}

/* Definition of execute function of SetCommand, Input is string arguement
 * If arguement is correct, deleteCoordinate() function of CoordinateCommander and returns
 * setSuccess, otherwise calls displayInfo function and returns setCommandFail.
 */
int SetCommand::execute(std::string s)
{
	if(s != "") //Arguement of coordinates
	{	
		float val1;
		float val2;
		stringstream ss(s);
		
		if(ss>>val1)
		{
			if(ss>>val2)
			{
				cc->SetCoordinate(val1,val2);
				return setSuccess;
			}
		}
	}
	displayInfo();
	return setCommandFail;

}

/* Delivers message to Serial PC User using CoordinateCommander */
void SetCommand::displayInfo() 
{
	cc->deliverMessage("Enter 'set [x] [y]' where [x] = 0.0-1.0 as left/right and [y] = 0.0-1.0 as down/top \n");
}
