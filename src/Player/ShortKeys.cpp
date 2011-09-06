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

void ShortKeys::keyPressed(IndigoPlayerEnum::ControlKey controlKey, int keyValue, unsigned short hardValue){
	if(hardwareTable.find(hardValue) != hardwareTable.end()){
		executeCommand(hardwareTable[hardValue]);
//		std::cout<<"void ShortKeys::keyPressed"<<std::endl;
	}else{
		if(convertTable.find(std::make_pair(controlKey, keyValue)) != convertTable.end()){
			executeCommand(convertTable[std::make_pair(controlKey, keyValue)]);
		}
	}
}

void ShortKeys::addList(Callable* object, std::list<IndigoPlayerEnum::Command> commands){
	std::list<IndigoPlayerEnum::Command>::iterator it;
	for(it = commands.begin(); it != commands.end(); it++){
		commandTable[*it] = object;
	}
}
void ShortKeys::executeCommand(IndigoPlayerEnum::Command command){
	if(commandTable.find(command) != commandTable.end()){
//		std::cout<<"void ShortKeys::executeCommand(IndigoPlayerEnum::Command command)"<<std::endl;
		commandTable[command]->call(command);
	}
//	std::cout<<"void ShortKeys::executeCommand(IndigoPlayerEnum::Command command) 2"<<std::endl;
}
void ShortKeys::setConvertTable(std::map<std::pair<IndigoPlayerEnum::ControlKey, int>, IndigoPlayerEnum::Command> table){
	convertTable = table;
}
void ShortKeys::setHardwareConvertTable(std::map<unsigned short, IndigoPlayerEnum::Command> table){
	hardwareTable = table;
}
