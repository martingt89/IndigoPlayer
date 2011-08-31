/*
 * KeyboardShortKeys.cpp
 *
 *  Created on: 30.8.2011
 *      Author: xgeier
 */

#include "ShortKeys.h"
#include <iostream>
ShortKeys::ShortKeys() {
	// TODO Auto-generated constructor stub
}

ShortKeys::~ShortKeys() {
	// TODO Auto-generated destructor stub
}

void ShortKeys::keyPressed(int control, int keyValue, unsigned short hardValue){
	if(hardwareTable.find(hardValue) != hardwareTable.end()){
		std::cout<<"Find hardware"<<std::endl;
		executeCommand(hardwareTable[hardValue]);
	}else{
		if(convertTable.find(std::make_pair(control, keyValue)) != convertTable.end()){
			std::cout<<"Find soft"<<std::endl;
			executeCommand(convertTable[std::make_pair(control, keyValue)]);
		}
	}
}

void ShortKeys::addList(Callable* object, std::list<IndigoPlayerCommand::Command> commands){
	std::list<IndigoPlayerCommand::Command>::iterator it;
	for(it = commands.begin(); it != commands.end(); it++){
		commandTable[*it] = object;
	}
}
void ShortKeys::executeCommand(IndigoPlayerCommand::Command command){
	if(commandTable.find(command) != commandTable.end()){
		std::cout<<"Find commad"<<std::endl;
		commandTable[command]->call(command);
	}
}
void ShortKeys::setConvertTable(std::map<std::pair<int, int>, IndigoPlayerCommand::Command> table){
	convertTable = table;
}
void ShortKeys::setHardwareConvertTable(std::map<unsigned short, IndigoPlayerCommand::Command> table){
	hardwareTable = table;
}
