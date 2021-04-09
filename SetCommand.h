#pragma once
#include "AbstractCommand.h"
#include "CoordinateCommander.h"

/*Declaration of class SetCommand, a public derived class of AbstractCommand*/
class SetCommand : public AbstractCommand {
public:
	SetCommand(CoordinateCommander* p_cc);
	virtual int execute(std::string s) override;
	virtual void displayInfo() override;
	virtual ~SetCommand() = default;
private: 
	CoordinateCommander* cc;
};
