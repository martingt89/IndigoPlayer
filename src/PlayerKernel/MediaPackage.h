/*
 * StringAnalyze.h
 *
 *  Created on: 11.8.2011
 *      Author: xgeier
 */

#ifndef STRINGANALYZE_H_
#define STRINGANALYZE_H_

#include <glibmm/dispatcher.h>
#include <glibmm/thread.h>
#include <cstdlib>
#include <string>
#include <map>
#include "SavedData.h"

class MediaPackage {
public:
	MediaPackage();
	virtual ~MediaPackage();
	int analyze(std::string);
	std::string getVariable(std::string variable);
	int getVariableAsInteger(std::string variable);
	Glib::Dispatcher message;
	void clear();
	void quitPlay();
	SavedData getSavedData();
	bool isVideoParamChange();
	int getValueFromSubtitlePath(std::string path);
	void setAktualPlaySubtitles(int number);
	bool subtitleChanged();
	std::list<Glib::ustring> getListSubtitles();
private:
	std::map<std::string, int> hashTable;
	std::map<std::string, std::string> valueTable;
	Glib::Mutex lock;
	bool changeVideoParam;
	std::list<std::pair<int, std::string> > loadedSubtitles;
	int lastNumber;
	std::string aktualPlaySubtitles;
	bool subChanged;
};

#endif /* STRINGANALYZE_H_ */
