/*
 * KeyboardShortKeys.h
 *
 *  Created on: 30.8.2011
 *      Author: xgeier
 */

#ifndef KEYBOARDSHORTKEYS_H_
#define KEYBOARDSHORTKEYS_H_

#include <map>
#include <list>
#include "../Interfaces/Callable.h"

class ShortKeys {
public:
	ShortKeys();
	virtual ~ShortKeys();
	void addList(Callable *object, std::list<IndigoPlayerCommand::Command> commands);
	void setHardwareConvertTable(std::map<unsigned short, IndigoPlayerCommand::Command> table);
	void setConvertTable(std::map<std::pair<int, int>, IndigoPlayerCommand::Command> table);
	void keyPressed(int control, int keyValue, unsigned short hardValue);
private:
	void executeCommand(IndigoPlayerCommand::Command command);
	std::map<IndigoPlayerCommand::Command, Callable*> commandTable;
	std::map<std::pair<int, int>, IndigoPlayerCommand::Command> convertTable;
	std::map<unsigned short, IndigoPlayerCommand::Command> hardwareTable;
};

#endif /* KEYBOARDSHORTKEYS_H_ */
