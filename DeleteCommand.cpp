
#include "DeleteCommand.h"

enum deleteReturn { deleteSuccess, deleteCommandFail};

using namespace std;

/* Constructor of DeleteCommand object, Input is pointer to CoordinateCommander object */
DeleteCommand::DeleteCommand(CoordinateCommander* p_cc) : cc(p_cc) //Constructor
{
}

/* Definition of execute function of DeleteCommand, Input is string ‘name’ arguement
 * If arguement is correct, deleteSave() function of CoordinateCommander and returns
 * deleteSuccess, otherwise calls displayInfo function and returns deleteCommandFail.
 */
int DeleteCommand::execute(std::string s)
{
	if(s != "") //Arguement of name
	{	
		if(!cc->deleteSave(s))
		{
			return deleteSuccess;
		}
	}
	displayInfo();
	return deleteCommandFail;

}

/* Delivers message to Serial PC User using CoordinateCommander */
void DeleteCommand::displayInfo() 
{
	cc->deliverMessage("Enter 'delete [name]' where [name] = name of saved coordinate to delete, use view command to see available options \n");
}
