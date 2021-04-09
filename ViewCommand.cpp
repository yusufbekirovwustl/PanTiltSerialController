
#include "ViewCommand.h"
enum viewReturn { viewSuccess, viewCommandFail};

using namespace std;

/* Constructor of ViewCommand object, Input is pointer to CoordinateCommander object */
ViewCommand::ViewCommand(CoordinateCommander* p_cc) : cc(p_cc) //Constructor
{
}

/* Definition of execute function of ViewCommand, Input is string arguement
 * If arguement is correct, viewSaved() function of CoordinateCommander and returns
 * viewSuccess, otherwise calls displayInfo function and returns viewCommandFail.
 */
int ViewCommand::execute(std::string s) 
{
	if(s == "") //No arguements
	{	
		if(!cc->viewSaved())
		{
			return viewSuccess;
		}
	}
	displayInfo();
	return viewCommandFail;

}

/* Delivers message to Serial PC User using CoordinateCommander */
void ViewCommand::displayInfo() 
{
	cc->deliverMessage("Enter 'view' to see saved coordinates\n");
}
