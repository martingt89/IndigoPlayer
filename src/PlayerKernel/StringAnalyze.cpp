/*
 * StringAnalyze.cpp
 *
 *  Created on: 11.8.2011
 *      Author: xgeier
 */

#include "StringAnalyze.h"

#include <iostream>

StringAnalyze::StringAnalyze() {
	hashTable["ID_LENGTH"] = 1;
	hashTable["ID_VIDEO_WIDTH"] = 1;
	hashTable["ID_VIDEO_HEIGHT"] = 1;
	hashTable["ID_VIDEO_ASPECT"] = 2;
	hashTable["ID_SEEKABLE"] = 1;
	hashTable["ANS_TIME_POSITION"] = 2;
}

StringAnalyze::~StringAnalyze() {
	// TODO Auto-generated destructor stub
}

void StringAnalyze::analyze(std::string text){
	unsigned int n = text.find('=', 0);
	if(n != std::string::npos){
		std::string identifier = std::string(text, 0, n);
		std::string value = std::string(text, n+1);
		if(hashTable[identifier]){
		//	std::cout<<identifier<<std::endl;
			if(hashTable[identifier] == 1 || hashTable[identifier] == 2)
				valueTable[identifier] = value;
			if(hashTable[identifier] == 2)
				message();
		}
	}
}
std::string StringAnalyze::getVariable(std::string variable){
	return valueTable[variable];
}
