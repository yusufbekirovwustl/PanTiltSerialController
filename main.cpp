/*
 * main.cpp
 * 
 * Yusuf Bekirov
 * 
 * This is the main driver for the PanTiltServoSerialController program.
 * 
 * 
 * 
 */
 
#include <stdio.h>
#include <iostream>
#include <string>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "pca9685.h"

#include "InputParser.h"
#include "pwmController.h"
#include "State.h"
#include "CoordinateCommander.h"

#include "PanCommand.h"
#include "SaveCommand.h"
#include "ViewCommand.h"
#include "DeleteCommand.h"
#include "LoadCommand.h"
#include "SetCommand.h"



#define PIN_BASE 300
#define HERTZ 50
#define I2C_LOC 0x40


enum mainReturn {mainSuccess, serialOpenError, wiringPiError, driverError};

using namespace std;

int main(int argc, char **argv)
{
	int serial_port; //Serial Device Descriptor
	string serial_device = "/dev/serial0"; //Set serial device to serial0
	if ((serial_port = serialOpen(serial_device.c_str(), 115200)) < 0) //Open serial_device with baud rate of 115200
	{
		//Check for serial device open error
		cout << "Unable to open serial device: " << serial_device << "\n" << endl;
		return serialOpenError;
	}
	if (wiringPiSetup() == -1)
	{
		//Check for wiringPi startup error
		cout << "Unable to start wiringPi\n" << endl;
		return wiringPiError;
	}
	
	// Setup servo driver with PIN_BASE and i2c location 0x40 (seen by i2cdetect -y 1)
	int fd = pca9685Setup(PIN_BASE, I2C_LOC, HERTZ);
	if (fd < 0)
	{
		cout << "Unable to setup pca9685 driver\n" << endl;
		return driverError;
	}

	pwmController * pwmC = new pwmController(PIN_BASE, HERTZ, 0.9, 2.5, .9, 2.5);
	InputParser * ip = new InputParser(serial_port); //Instantiate InputParser class with serial_port 
	State * s = new State(pwmC);
	CoordinateCommander * c = new CoordinateCommander(s,serial_port);
	
	AbstractCommand * acp = new PanCommand(c);
	AbstractCommand * acs = new SaveCommand(c);
	AbstractCommand * acv = new ViewCommand(c);
	AbstractCommand * acd = new DeleteCommand(c);
	AbstractCommand * acl = new LoadCommand(c);
	AbstractCommand * acset = new SetCommand(c);
	
	ip->addCommand("pan",acp);
	ip->addCommand("save",acs);
	ip->addCommand("view",acv);
	ip->addCommand("delete",acd);
	ip->addCommand("load",acl);
	ip->addCommand("set", acset);
	
	ip->run();
	
	delete pwmC;
	delete ip;
	delete s;
	delete c;
	delete acp;
	delete acs;
	delete acv;
	delete acd;
	delete acl;
	delete acset;
	
	return mainSuccess;
}

