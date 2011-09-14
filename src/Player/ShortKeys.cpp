/*
 * KeyboardShortKeys.cpp
 *
 *  Created on: 30.8.2011
 *      Author: xgeier
 */

#include "ShortKeys.h"
#include <iostream>
ShortKeys::ShortKeys() {
	std::map<std::pair<IndigoPlayerEnum::ControlKey, int>, IndigoPlayerEnum::Command> table;
	table[std::make_pair(IndigoPlayerEnum::NONE, 102)] = IndigoPlayerEnum::FULLUNFULLSCR;
	table[std::make_pair(IndigoPlayerEnum::NONE, 109)] = IndigoPlayerEnum::MUTEUNMUTE;
	table[std::make_pair(IndigoPlayerEnum::NONE, 103)] = IndigoPlayerEnum::SUBFORWARD;
	table[std::make_pair(IndigoPlayerEnum::NONE, 104)] = IndigoPlayerEnum::SUBBACKWARD;
	setConvertTable(table);
	std::map<short unsigned, IndigoPlayerEnum::Command> hTable;
	hTable[9] = IndigoPlayerEnum::UNFULLSCR;
	hTable[10] = IndigoPlayerEnum::HALFSIZE;
	hTable[11] = IndigoPlayerEnum::ORIGINALSIZE;
	hTable[12] = IndigoPlayerEnum::MAXIMALIZESIZE;
	hTable[13] = IndigoPlayerEnum::FULLSCR;
	hTable[14] = IndigoPlayerEnum::TOTALSIZE;
	hTable[65] = IndigoPlayerEnum::PLAYSTOPBUT;

	hTable[114] = IndigoPlayerEnum::SHORFORWARD;
	hTable[113] = IndigoPlayerEnum::SHORBACKWARD;
	hTable[111] = IndigoPlayerEnum::LONGFORWARD;
	hTable[116] = IndigoPlayerEnum::LONGBACKWARD;
	setHardwareConvertTable(hTable);
}

ShortKeys::~ShortKeys() {
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
