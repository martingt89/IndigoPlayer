/*
 * StringAnalyze.cpp
 *
 *  Created on: 11.8.2011
 *      Author: xgeier
 */

#include "MediaPackage.h"

#include <iostream>

MediaPackage::MediaPackage() {
	hashTable["ID_LENGTH"] = 4;
	hashTable["ID_VIDEO_WIDTH"] = 4;
	hashTable["ID_VIDEO_HEIGHT"] = 4;
	hashTable["Starting playback..."] = 1;
	hashTable["ID_SEEKABLE"] = 4;
	hashTable["ANS_TIME_POSITION"] = 3;
	hashTable["ID_EXIT"] = 2;
	hashTable["ID_FILE_SUB_ID"] = 5;
	hashTable["ID_FILE_SUB_FILENAME"] = 6;
	changeVideoParam = false;
	lastNumber = 0;
	aktualPlaySubtitles = "";
}

MediaPackage::~MediaPackage() {
	// TODO Auto-generated destructor stub
}

int MediaPackage::analyze(std::string text) {
	unsigned int n = text.find('=', 0);
	std::string identifier = std::string(text, 0, n);
	std::string value = std::string(text, n + 1);
	int vauleI;
	if (hashTable[identifier]) {
		vauleI = hashTable[identifier];
		if (vauleI == 4)
			changeVideoParam = true;
		if (vauleI == 1 || vauleI == 2) {
			return hashTable[identifier];
		}
		if (vauleI == 4 || vauleI == 3) {
			lock.lock();
			valueTable[identifier] = value;
			lock.unlock();
		}
		if (vauleI == 3)
			message();
		if (vauleI == 5)
			lastNumber = atoi(value.c_str());
		if (vauleI == 6) {
			std::pair<int, std::string> pair(lastNumber, value);
			lock.lock();
			loadedSubtitles.push_back(pair);
			lock.unlock();
		}
	}
	return 0;
}
void MediaPackage::clear() {
	valueTable.clear();
	changeVideoParam = true;
}
void MediaPackage::quitPlay() {
	lock.lock();
	valueTable["EXIT"] = "true";
	lock.unlock();
	message();
}
std::string MediaPackage::getVariable(std::string variable) {
	std::string var = "";
	lock.lock();
	var = valueTable[variable];
	lock.unlock();
	return var;
}
int MediaPackage::getVariableAsInteger(std::string variable) {
	return atoi(getVariable(variable).c_str());
}
SavedData MediaPackage::getSavedData() {
	SavedData data;
	lock.lock();
	data.setResolution(atoi(valueTable["ID_VIDEO_WIDTH"].c_str()),
			atoi(valueTable["ID_VIDEO_HEIGHT"].c_str()));
	data.setPosition(atof(valueTable["ANS_TIME_POSITION"].c_str()));
	lock.unlock();
	data.setSubtitle(aktualPlaySubtitles);
	return data;
}
bool MediaPackage::isVideoParamChange() {
	bool is = changeVideoParam;
	changeVideoParam = false;
	return is;
}
int MediaPackage::getValueFromSubtitlePath(std::string path) {
	int find = -1;
	std::list<std::pair<int, std::string> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->second == path) {
			find = it->first;
			break;
		}
	}
	lock.unlock();
	return find;
}
void MediaPackage::setAktualPlaySubtitles(int number) {
	if(number == -1){
		aktualPlaySubtitles = "";
		return;
	}
	std::list<std::pair<int, std::string> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->first == number) {
			aktualPlaySubtitles = it->second;
			break;
		}
	}
	lock.unlock();
}
