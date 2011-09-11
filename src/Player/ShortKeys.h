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
#include "../EnumTypes.h"

class ShortKeys {
public:
	ShortKeys();
	virtual ~ShortKeys();
	void addList(Callable *object, std::list<IndigoPlayerEnum::Command> commands);
	void setHardwareConvertTable(std::map<unsigned short, IndigoPlayerEnum::Command> table);
	void setConvertTable(std::map<std::pair<IndigoPlayerEnum::ControlKey, int>, IndigoPlayerEnum::Command> table);
	void keyPressed(IndigoPlayerEnum::ControlKey controlKey, int keyValue, unsigned short hardValue);
private:
	void executeCommand(IndigoPlayerEnum::Command command);
	std::map<IndigoPlayerEnum::Command, Callable*> commandTable;
	std::map<std::pair<IndigoPlayerEnum::ControlKey, int>, IndigoPlayerEnum::Command> convertTable;
	std::map<unsigned short, IndigoPlayerEnum::Command> hardwareTable;
};

#endif /* KEYBOARDSHORTKEYS_H_ */
