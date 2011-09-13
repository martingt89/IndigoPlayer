/*
 * StringAnalyze.cpp
 *
 *  Created on: 11.8.2011
 *      Author: xgeier
 */

#include "MediaPackage.h"

#include <iostream>

//Could not open/initialize audio device -> no sound.

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
	// Errors
	hashTable["Could not open/initialize audio device -> no sound."] = 10;
	changeVideoParam = false;
	subChanged = false;
	audChanged = false;
	unknownCounter = 0;
	lastNumberSubtitle = 0;
	lastNumberAudio = 0;


	start = false;
	end = false;
	firstEnd = false;
}

MediaPackage::~MediaPackage() {
}

int MediaPackage::analyze(std::string text) {
	unsigned int n = text.find('=', 0);
	std::string identifier = std::string(text, 0, n);
	std::string value = std::string(text, n + 1);
	int vauleI;
	bool mess = false;
	if (hashTable[identifier]) {
		vauleI = hashTable[identifier];
		if(vauleI == 1){
			start = true;
			mess = true;
		}
		if(vauleI == 2){
			end = true;
			firstEnd = true;
			mess = true;
		}
		if (vauleI == 3)
			mess = true;
		if (vauleI == 3 || vauleI == 4) {
			lock.lock();
			valueTable[identifier] = value;
			lock.unlock();
		}
		if (vauleI == 4)
			changeVideoParam = true;
		if (vauleI == 5) {
			lastNumberSubtitle = atoi(value.c_str());
		}
		if (vauleI == 6) {
			lock.lock();
			loadedSubtitles.push_back(std::make_pair(lastNumberSubtitle, StreamInfo(value, false)));
			lock.unlock();
			subChanged = true;
			mess = true;
		}
		if (vauleI == 7) {
			lastNumberAudio = atoi(value.c_str());
		}
		if(mess)
			message();
	}
	std::list<std::pair<int, StreamInfo> >::iterator it;
	if (Glib::ustring(identifier, 0, 7) == "ID_SID_") {
		if (value == "und") {
			value = "Unknown";
		}
		lock.lock();
		if (loadedSubtitles.size() > 0) {
			it = loadedSubtitles.end();
			it--;
			if (lastNumberSubtitle == it->first)
				it->second.name += " - " + value;
			else
				loadedSubtitles.push_back(std::make_pair(lastNumberSubtitle, StreamInfo(value, true)));
		} else {
			loadedSubtitles.push_back(std::make_pair(lastNumberSubtitle, StreamInfo(value, true)));
		}
		lock.unlock();
		subChanged = true;
		message();
	}
	if (Glib::ustring(identifier, 0, 7) == "ID_AID_") {
		if (value == "und") {
			value = "Unknown ";
		}
		lock.lock();
		if (loadedAudio.size() > 0) {
			it = loadedAudio.end();
			it--;
			if (it->first == lastNumberAudio) {
				it->second.name += " - " + value;
			} else {
				loadedAudio.push_back(std::make_pair(lastNumberAudio, StreamInfo(value, true)));
			}
		} else {
			loadedAudio.push_back(std::make_pair(lastNumberAudio, StreamInfo(value, true)));
		}
		lock.unlock();
		audChanged = true;
		message();
	}
	return 0;
}
void MediaPackage::analyzeErrors(Glib::ustring text){
	if(hashTable.find(text) != hashTable.end()){

	}
}
void MediaPackage::sendExit(){
	if(firstEnd != true){
		analyze("ID_EXIT");
	}
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

bool MediaPackage::isVideoParamChange() {
	bool is = changeVideoParam;
	changeVideoParam = false;
	return is;
}
bool MediaPackage::isStart(bool off){
	if(start){
		if(off)
			start = false;
		return true;
	}
	return false;
}
bool MediaPackage::isEnd(bool off){
	if(end){
		if(off)
			end = false;
		return true;
	}
	return false;
}
bool MediaPackage::isSubtitleChanged() {
	bool tmp = subChanged;
	subChanged = false;
	return tmp;
}
bool MediaPackage::isAudioChanged() {
	bool tmp = audChanged;
	audChanged = false;
	return tmp;
}
bool MediaPackage::isVideoChanged() {
	return false;
}

int MediaPackage::getSubtitleNumberFromName(std::string name) {
	int find = -1;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if ((it->second).name == name) {
			find = it->first;
			break;
		}
	}
	lock.unlock();
	return find;
}
int MediaPackage::getAudioNumberFromName(std::string name) {
	int find = -1;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	lock.lock();
	for (it = loadedAudio.begin(); it != loadedAudio.end(); it++) {
		if (it->second.name == name) {
			find = it->first;
			break;
		}
	}
	lock.unlock();
	return find;
}

bool MediaPackage::isOriginalSubtitleFromName(Glib::ustring name) {
	std::list<std::pair<int, StreamInfo> >::iterator it;
	bool in = false;
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->second.name == name) {
			in = it->second.inside;
			break;
		}
	}
	lock.unlock();
	return in;
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
Glib::ustring MediaPackage::getAudioNameFromNumber(int number) {
	std::list<Glib::ustring> list;
	std::list<std::pair<int, StreamInfo> >::iterator it;
	Glib::ustring text = "";
	lock.lock();
	for (it = loadedAudio.begin(); it != loadedAudio.end(); it++) {
		if(it->first == number){
			text = it->second.name;
			break;
		}
	}
	lock.unlock();
	return text;
}
Glib::ustring MediaPackage::getSubtitleNameFromNumber(int number, bool orig) {
	std::list<std::pair<int, StreamInfo> >::iterator it;
	Glib::ustring text = "";
	lock.lock();
	for (it = loadedSubtitles.begin(); it != loadedSubtitles.end(); it++) {
		if (it->first == number && it->second.inside == orig) {
			text = it->second.name;
			break;
		}
	}
	lock.unlock();
	return text;
}
//===================================================================================
void MediaPackage::clear() {
	lock.lock();
	valueTable.clear();
	loadedSubtitles.clear();
	loadedAudio.clear();
	lock.unlock();
	changeVideoParam = false;
	subChanged = false;
	audChanged = false;
	firstEnd = false;
}
