
#include <iostream>
#include <sstream>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "pca9685.h"
#include "InputParser.h"

enum inputParserReturn { inputParserSuccess, mapInsertFail, inputParserQuit };

using namespace std;

/* Constructor definition for InputParser, Input is serial_ports file decriptor*/
InputParser::InputParser(int p_serial_port) : serial_port(p_serial_port) 
{
}

/* addCommand method definition for InputParser.Input is string and pointer to AbstractCommand
*  Adds a string key and pointer to AbstractCommand value to 'm' map.
*  Returns inputParserSuccess on success, otherwise mapInsertFail.
*/
int InputParser::addCommand(string s, AbstractCommand * ac) {
  unsigned int minitialsize = this->m.size(); //Used to check if map insert is successful
  this->m.insert({ s,ac }); //Insertion of command to map of commands
  if (this->m.size() == (minitialsize+1)) 
  {
      return inputParserSuccess;
  }
  return mapInsertFail;
}

/* run method definition for InputParser.
*  Parses string returned by prompt method.
*  If correct command with correct arguements, calls execute on correct AbstractCommand pointer.
*  If correct command with incorrect arguements, calls displayInfo on correct AbstractCommand pointer.
*  If help command in InputParser, calls listCommands function
*  If q command, returns inputParserQuit
*  If incorrect command, calls prompt() again
*/
int InputParser::run ()
{
  string inputString;
  while (1) 
  {
    inputString = this->prompt();
    //cout << "Input String: " << inputString << endl;
    if(inputString.size()) //if size of input > 0
    {
		if (inputString == "q") //q quits the program
		{
		  std::cout << "User has quit!" << std::endl;
		  return inputParserQuit;
		}
		else if (inputString == "help") 
		{
		  listCommands(); //help returns list of commands
		}
		else if (!inputString.find(' ')) //Command w/o arguement
		{
		  std::map<std::string, AbstractCommand*>::iterator aci = this->m.find(inputString);
		  if (aci == this->m.end()) //Look for command
		  {
		    serialPrintf(this->serial_port, "Command Does Not Exist \n");
		  }
		  else 
		  {
		    int i = aci->second->execute(""); //call execute on command 
		    if (i)
		    {
		      serialPrintf(this->serial_port, "Command Does Not Exist \n");
		    }
		  }
		}
		else //Commands with arguements
		{
		  std::istringstream iss(inputString);
		  std::string firstWord;
		  iss >> firstWord;
		  if(firstWord == "help")
		  {
		     std::string secondWord;
		     iss >> secondWord;
		     std::map<std::string, AbstractCommand*>::iterator aci = this->m.find(secondWord);
		     if (aci == this->m.end()) //Look for command
		     {
		       serialPrintf (this->serial_port, "Command Does Not Exist \n");
		     }
		     else
		     {
			aci->second->displayInfo(); //Display help for specified command
		     }
		  }
		  else
		  {
		    std::map<std::string, AbstractCommand*>::iterator aci = this->m.find(firstWord);
		    if (aci == this->m.end()) //Look for Command
		    {
		      serialPrintf (this->serial_port, "Command Does Not Exist \n");
		    }
		    else
		    {
		      std::string secondWord;
		      iss.ignore(256, ' '); //Ignore the space after first word, saving all that come after
		      getline(iss, secondWord);
		      iss >> secondWord;
		      int i = aci->second->execute(secondWord); //Call execute on command
		      if (i)
		      {
				serialPrintf (this->serial_port, "Command Failed \n");
		      }
		    }
		  }
		}
		inputString = ""; //clear string
	}	
  }
}

/* listCommands method definition for InputParser.
*  Iterates through 'm' map to list supported Commands.
*/
void InputParser::listCommands()
{
  for (std::map<std::string,AbstractCommand *>::iterator i = this->m.begin(); i != this->m.end(); i++)
  {
    serialPrintf(this->serial_port, (i->first).c_str());
    serialPrintf(this->serial_port, "\n");
    //cout << i->first << endl;
  }
}

/* prompt method definition for InputParser.
*  Loops until data available from serial port, where a string is constructed
*  from characters until a carriage return is seen, the input string is returned.
*/
string InputParser::prompt()
{
  serialPrintf(this->serial_port, "\n Enter command, 'q' to quit, 'help', or 'help <command_name>' \n");
  serialPrintf(this->serial_port, "$");
  //cout << "Enter command, 'q' to quit, 'help', or 'help <command_name>'" << std::endl;
  string input;
  while (1) {
		
    if(serialDataAvail(this->serial_port) > 0)
    {	
      char c = serialGetchar(this->serial_port);
      if(c != '\n' && c!= '\r') //For non new-line return
      {
	input += c;
      }
    
      if(c == '\r') //Carriage return denotes enter from user, parse string
      {
	serialPrintf(this->serial_port, "\n");
	return input;
      }
    }
  }
  return input;
}
