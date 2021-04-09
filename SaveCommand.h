#pragma once
#include "AbstractCommand.h"
#include "CoordinateCommander.h"

/*Declaration of class SaveCommand, a public derived class of AbstractCommand*/
class SaveCommand : public AbstractCommand {
public:
	SaveCommand(CoordinateCommander* p_cc);
	virtual int execute(std::string s) override;
	virtual void displayInfo() override;
	virtual ~SaveCommand() = default;
private: 
	CoordinateCommander* cc;
};
