
#include "LoadCommand.h"

enum loadReturn { loadSuccess, loadCommandFail};

using namespace std;

/* Constructor of LoadCommand object,Input is pointer to CoordinateCommander object */
LoadCommand::LoadCommand(CoordinateCommander* p_cc) : cc(p_cc) //Constructor
{
}

/* Definition of execute function of LoadCommand, Input is string arguement
 * If arguement is correct, restoreCoordinate function of CoordinateCommander and returns
 * loadSuccess, otherwise calls displayInfo function and returns loadCommandFail.
 */
int LoadCommand::execute(std::string s) 
{
	if(s != "") //Arguement of name
	{	
		if(!cc->restoreCoordinate(s))
		{
			return loadSuccess;
		}
	}
	displayInfo();
	return loadCommandFail;

}

/* Delivers message to Serial PC User using CoordinateCommander */
void LoadCommand::displayInfo() 
{
	cc->deliverMessage("Enter 'load [name]' where [name] = name of saved coordinate to load, use view command to see available options \n");
}
