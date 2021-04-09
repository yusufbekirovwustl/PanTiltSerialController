#pragma once
#include "AbstractCommand.h"
#include "CoordinateCommander.h"

/*Declaration of class ViewCommand, a public derived class of AbstractCommand*/
class ViewCommand : public AbstractCommand {
public:
	ViewCommand(CoordinateCommander* p_cc);
	virtual int execute(std::string s) override;
	virtual void displayInfo() override;
	virtual ~ViewCommand() = default;
private: 
	CoordinateCommander* cc;
};
