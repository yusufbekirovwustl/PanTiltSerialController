#pragma once
#include "AbstractCommand.h"
#include "CoordinateCommander.h"

/*Declaration of class LoadCommand, a public derived class of AbstractCommand*/
class LoadCommand : public AbstractCommand {
public:
	LoadCommand(CoordinateCommander* p_cc);
	virtual int execute(std::string s) override;
	virtual void displayInfo() override;
	virtual ~LoadCommand() = default;
private: 
	CoordinateCommander* cc;
};
