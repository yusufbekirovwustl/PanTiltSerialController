#include <wiringPi.h>
#include <wiringSerial.h>
#include "CoordinateCommander.h"
#include <string> 
#include <iostream>

using namespace std;

enum coordinateCommanderReturn{ coordinateCommanderSuccess, coordinateCommanderMapInsertFail, coordinateCommanderRestoreFail, coordinateCommanderDeleteFail};

/* Constructor of CoordinateCommander object, Input is State pointer and serial_port file descriptor
*/
CoordinateCommander::CoordinateCommander(State * p_state,int p_serial_port) : state(p_state), serial_port(p_serial_port) //Constructor
{
}

/* Definition of saveCoordinate function of CoordinateCommander, Input is string ‘name’ arguement
 * Calls on createStateSnapshot of ‘state’ State object to return a StateSnapshot object pointer
 * Uses string input as key and newly created pointer as value to insert into ‘snap’ map object.
 * Returns coordinateCommanderSuccess on successful map insertion, otherwise
 *  coordinateCommanderMapInsertFail
 */
int CoordinateCommander::saveCoordinate(string s)
{
	StateSnapshot * ss = state->createStateSnapshot(); //Get current State
	unsigned int minitialsize = this->snap.size(); //Used to check if map insert is successful
	this->snap.insert({ s,ss }); //Save StateSnapshot
	if (this->snap.size() == (minitialsize+1)) 
	{
		return coordinateCommanderSuccess;
	}
	return coordinateCommanderMapInsertFail;
}


/* Definition of restoreCoordinate function of CoordinateCommander, Input is string ‘name’ arguement
 * Calls on find on ‘snap’ map using string argument to access correct StateSnapshot
 * Calls restoreOne and restoreTwo in StateSnapshot if found and returns coordinateCommanderSuccess
 *  otherwise, coordinateCommanderRestoreFail
 */
int CoordinateCommander::restoreCoordinate(string s)
{
	map<string, StateSnapshot*>::iterator snapIterate = this->snap.find(s);
	if(snapIterate != this->snap.end())
	{
		snapIterate->second->restoreOne(); //Restore aquired StateSnapshot
		snapIterate->second->restoreTwo();
		return coordinateCommanderSuccess;
	}
	deliverMessage("Cannot find restore name in memory, try using view command to see current entries \n");
	return coordinateCommanderRestoreFail;
	
}

/* Definition of viewSaved function of CoordinateCommander
 * Iterates through ‘snap’ map, uses deliverMessage to display names of keys on PC Serial
 * Returns coordinateCommanderSuccess
 */
int CoordinateCommander::viewSaved()
{
	deliverMessage("Coordinates: \n");
	for(map<string, StateSnapshot*>::iterator i = this->snap.begin(); i != this->snap.end(); i++)
	{
		deliverMessage(i->first);
		deliverMessage("\n");
	}
	deliverMessage("\n");
	return coordinateCommanderSuccess;
}

/* Definition of SetCoordinate function of CoordinateCommander, Input is two float ‘coordinate’ arguements
 * Creates a new StateSnapshot using ‘state’ State and the two float arguments
 * If float p_one is positive, uses StateSnapshot to call restoreOne
 * If float p_two is positive, uses StateSnapshot to call restoreTwo
 * Returns coordinateCommanderSuccess
 */
int CoordinateCommander::SetCoordinate(float p_one, float p_two)
{
	StateSnapshot * ss = new StateSnapshot(this->state, p_one,p_two);
	if(p_two == -1)
	{
		ss->restoreOne(); //Restore w/o Saving
	}
	else if(p_one == -1)
	{
		ss->restoreTwo(); //Restore w/o Saving
	}
	else
	{
		ss->restoreOne();
		ss->restoreTwo(); //Restore w/o Saving
	}
	return coordinateCommanderSuccess;
}

/* Definition of SetRelCoordinate function of CoordinateCommander, Input is two float ‘coordinate’ arguements
 * Calls createStateSnapshot using ‘state’
 * Views current state values using State snapshot to adjust using the float values provided
 * Uses SetCoordinate using the adjusted float values
 * Returns coordinateCommanderSuccess
 */
int CoordinateCommander::SetRelCoordinate(float adjustOne,float adjustTwo)
{
	StateSnapshot * ss_old = state->createStateSnapshot(); //Get current StateSnapshot
	float currentOne = ss_old->viewOne();
	float currentTwo = ss_old->viewTwo();
	if(adjustOne != 0.0 && adjustTwo != 0.0)
	{
		currentOne += adjustOne;
		currentTwo += adjustTwo;
	}
	else if(adjustOne != 0.0)
	{
		currentOne += adjustOne;
		currentTwo = -1;
	}
	else
	{
		currentOne = -1;
		currentTwo += adjustTwo;
	}
	SetCoordinate(currentOne,currentTwo);
	return coordinateCommanderSuccess;
}

/* Definition of deleteSave function of CoordinateCommander, Input is string ‘name’ arguement
 * Calls erase ‘snap’ on map using string arguement
 * If value erased, returns coordinateCommanderSuccess, otherwise coordinateCommanderDeleteFail
 */
int CoordinateCommander::deleteSave(string s)
{
	if(snap.erase(s)){
		return coordinateCommanderSuccess;
	}
	return coordinateCommanderDeleteFail;
}

/* Definition of deliverMessage function of CoordinateCommander, Input is string ‘input’ arguement
 * Uses serialPrintf of wiringPi library to deliver input message to PC Serial Port User
 */
void CoordinateCommander::deliverMessage(string s)
{
	serialPrintf(this->serial_port, s.c_str());
}
