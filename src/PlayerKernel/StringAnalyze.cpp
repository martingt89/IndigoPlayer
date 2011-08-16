/*
 * StringAnalyze.cpp
 *
 *  Created on: 11.8.2011
 *      Author: xgeier
 */

#include "StringAnalyze.h"

#include <iostream>

StringAnalyze::StringAnalyze() {
	hashTable["ID_LENGTH"] = 4;
	hashTable["ID_VIDEO_WIDTH"] = 4;
	hashTable["ID_VIDEO_HEIGHT"] = 4;
	hashTable["Starting playback..."] = 1;
	hashTable["ID_SEEKABLE"] = 4;
	hashTable["ANS_TIME_POSITION"] = 3;
	hashTable["ID_EXIT"] = 2;
}

StringAnalyze::~StringAnalyze() {
	// TODO Auto-generated destructor stub
}

int StringAnalyze::analyze(std::string text) {
	unsigned int n = text.find('=', 0);
//	std::cout<<text<<std::endl;
//	if (n != std::string::npos) {
		std::string identifier = std::string(text, 0, n);
		std::string value = std::string(text, n + 1);
		if (hashTable[identifier]) {
		//		std::cout<<identifier<<std::endl;
			if (hashTable[identifier] == 1 || hashTable[identifier] == 2) {
				return hashTable[identifier];
			}
			if (hashTable[identifier] == 4 || hashTable[identifier] == 3){
				lock.lock();
				valueTable[identifier] = value;
				lock.unlock();
			}
			if (hashTable[identifier] == 3)
				message();
		}
//	}
	return 0;
}
void StringAnalyze::clear() {
	valueTable.clear();
}
void StringAnalyze::quitPlay() {
	lock.lock();
	valueTable["EXIT"] = "true";
	lock.unlock();
	message();
}
std::string StringAnalyze::getVariable(std::string variable) {
	std::string var = "";
	lock.lock();
	var = valueTable[variable];
	lock.unlock();
	return var;
}
SavedData StringAnalyze::getSavedData(){
	SavedData data;
	lock.lock();
//	std::cout<<"w: "<<atoi(valueTable["ID_VIDEO_WIDTH"].c_str())<<" h: "<<atoi(valueTable["ID_VIDEO_HEIGHT"].c_str());
	data.setResolution(atoi(valueTable["ID_VIDEO_WIDTH"].c_str()), atoi(valueTable["ID_VIDEO_HEIGHT"].c_str()));
	data.setPosition(atof(valueTable["ANS_TIME_POSITION"].c_str()));
	lock.unlock();
	return data;
}
