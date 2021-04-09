
#include "SaveCommand.h"
enum saveReturn { saveSuccess, saveCommandFail};

using namespace std;

/* Constructor of SaveCommand object, Input is pointer to CoordinateCommander object*/
SaveCommand::SaveCommand(CoordinateCommander* p_cc) : cc(p_cc) //Constructor
{
}

/* Definition of execute function of SaveCommand, Input is string ‘name’ arguement
 * If arguement is correct, callssaveCoordinate function of CoordinateCOmmander and returns
 * saveSuccess, otherwise calls displayInfo function and returns saveCommandFail.
 */
int SaveCommand::execute(std::string s)
{
	if(s != "") 
	{	
		if(!cc->saveCoordinate(s))
		{
			cc->deliverMessage("Coordinate saved! \n");
			return saveSuccess;
		}
	}
	displayInfo();
	return saveCommandFail;

}

/* Delivers message to Serial PC User using CoordinateCommander */
void SaveCommand::displayInfo() 
{
	cc->deliverMessage("Enter 'save [name]' where [name] = name of savefile for current position \n");
}
