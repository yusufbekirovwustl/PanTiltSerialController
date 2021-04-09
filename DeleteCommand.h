#pragma once
#include "AbstractCommand.h"
#include "CoordinateCommander.h"

/*Declaration of class DeleteCommand, a public derived class of AbstractCommand*/
class DeleteCommand : public AbstractCommand {
public:
	DeleteCommand(CoordinateCommander* p_cc);
	virtual int execute(std::string s) override;
	virtual void displayInfo() override;
	virtual ~DeleteCommand() = default;
private: 
	CoordinateCommander* cc;
};
