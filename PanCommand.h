#pragma once
#include "AbstractCommand.h"
#include "CoordinateCommander.h"

/*Declaration of class PanCommand, a public derived class of AbstractCommand*/
class PanCommand : public AbstractCommand {
public:
	PanCommand(CoordinateCommander* p_cc);
	virtual int execute(std::string s) override;
	virtual void displayInfo() override;
	virtual ~PanCommand() = default;
private: 
	CoordinateCommander* cc;
};

//enum panReturn;
