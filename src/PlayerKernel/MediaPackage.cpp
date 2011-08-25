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
	hashTable["ID_AUDIO_ID"] = 7;
	hashTable["ID_SUBTITLE_ID"] = 5;
	changeVideoParam = false;
	subChanged = false;
	audChanged = false;
	unknownCounter = 0;
	lastNumberSubtitle = 0;
	lastNumberAudio = 0;
	aktualPlaySubtitles = -1;
	aktualPlaySubtitlesStr = "";
	aktualPlayAudioStr = "";
	aktualPlayAudio = -1;
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
		if (vauleI == 5) {
			lastNumberSubtitle = atoi(value.c_str());
		}
		if (vauleI == 6) {
			lock.lock();
			loadedSubtitles.push_back(std::make_pair(lastNumberSubtitle, StreamInfo(value, false)));
			lock.unlock();
			subChanged = true;
		}
		if (vauleI == 7) {
			lastNumberAudio = atoi(value.c_str());
		}
	}
	if (Glib::ustring(identifier, 0, 7) == "ID_SID_") {
		if (value == "und") {
			value = "Unknown";
		}
		lock.lock();
		loadedSubtitles.push_back(std::make_pair(lastNumberSubtitle, StreamInfo(value, true)));
		lock.unlock();
		subChanged = true;
	}
	if (Glib::ustring(identifier, 0, 7) == "ID_AID_") {
		if (value == "und") {
			value = "Unknown ";
		}
		if (lastNumberAudio == 0) {
			value = value + " - Original";
		}
		lock.lock();
		loadedAudio.push_back(std::make_pair(lastNumberAudio, StreamInfo(value, true)));
		lock.unlock();
		audChanged = true;
	}
	return 0;
}
void MediaPackage::clear() {
	std::cout<<"clear"<<std::endl;
	lock.lock();
	valueTable.clear();
	loadedSubtitles.clear();
	loadedAudio.clear();
	lock.unlock();
	changeVideoParam = true;
	subChanged = false;
	audChanged = false;

}
void MediaPackage::quitPlay() {
	lock.lock();
	valueTable["EXIT"] = "true";
	lock.unlock();
	message();
	aktualPlaySubtitles = -1;
	aktualPlaySubtitlesStr = "";
	aktualPlayAudioStr = "";
	aktualPlayAudio = -1;
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
	data.setSubtitleID(aktualPlaySubtitles);
	data.setSubtitlePath(aktualPlaySubtitlesStr);
	data.setAudioID(aktualPlayAudio);
	data.setAudioPath(aktualPlayAudioStr);

	return data;
}
bool MediaPackage::isVideoParamChange() {
	bool is = changeVideoParam;
	changeVideoParam = false;
	return is;
}
int MediaPackage::getValueFromSubtitlePath(std::string path) {
	int find = -1;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if ((it->second).name == path) {
			find = it->first;
			break;
		}
	}
	lock.unlock();
	return find;
}
int MediaPackage::getValueFromAudioText(std::string text) {
	int find = -1;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedAudio.begin(); it != loadedAudio.end(); it++) {
		if (it->second.name == text) {
			find = it->first;
			break;
		}
	}
	lock.unlock();
	return find;
}
void MediaPackage::setAktualPlaySubtitles(int number) {
	aktualPlaySubtitles = number;
	aktualPlaySubtitlesStr = "";
}
void MediaPackage::setAktualPlaySubtitles(std::string path){
	aktualPlaySubtitles = -1;
	aktualPlaySubtitlesStr = path;
}
bool MediaPackage::isOriginalSubtitleStream(int number) {
	if (number == -1)
		return true;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->first == number) {
			lock.unlock();
			return it->second.inside;
		}
	}
	lock.unlock();
	return false;
}
bool MediaPackage::isOriginalAudioStream(int number) {
	if (number == -1)
		return true;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->first == number) {
			lock.unlock();
			return it->second.inside;
		}
	}
	lock.unlock();
	return false;
}
std::string MediaPackage::getPathOfStream(int number) {
	if (number == -1)
		return "";
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->first == number) {
			lock.unlock();
			return it->second.name;
		}
	}
	lock.unlock();
	return "";
}
void MediaPackage::setAktualPlayAudio(int number) {
	aktualPlayAudio = number;
	aktualPlayAudioStr = "";
}
void MediaPackage::setAktualPlayAudio(std::string path) {
	aktualPlayAudio = -1;
	aktualPlayAudioStr = path;
}
bool MediaPackage::subtitleChanged() {
	bool tmp = subChanged;
	subChanged = false;
	return tmp;
}
bool MediaPackage::audioChanged() {
	bool tmp = audChanged;
	audChanged = false;
	return tmp;
}
std::list<Glib::ustring> MediaPackage::getListSubtitles() {
	std::list<Glib::ustring> list;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		list.push_back(it->second.name);
	}
	lock.unlock();
	return list;
}
std::list<Glib::ustring> MediaPackage::getListAudios() {
	std::list<Glib::ustring> list;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedAudio.begin(); it != loadedAudio.end(); it++) {
		list.push_back(it->second.name);
	}
	lock.unlock();
	return list;
}
