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
#include <glibmm/ustring.h>
#include <cstdlib>
#include <string>
#include <map>
#include "SavedData.h"
class StreamInfo {
public:
	StreamInfo(){
		inside = false;
		name = "";
	};
	StreamInfo(std::string n, bool i){
		name = n;
		inside = i;
	};
	std::string name;
	bool inside;
};
class MediaPackage {
public:
	MediaPackage();
	virtual ~MediaPackage();
	int analyze(std::string);
	std::string getVariable(std::string variable);
	int getVariableAsInteger(std::string variable);
	Glib::Dispatcher message;
	//------------------------------------------------
	void clear();
	void quitPlay();
	SavedData getSavedData();
	bool isVideoParamChange();

	int getValueFromSubtitlePath(std::string path);
	int getValueFromAudioText(std::string text);

	void setAktualPlaySubtitles(int number);
	void setAktualPlaySubtitles(std::string path);
	void setAktualPlayAudio(int number);
	void setAktualPlayAudio(std::string path);

	bool subtitleChanged();
	bool audioChanged();
	std::list<Glib::ustring> getListSubtitles();
	std::list<Glib::ustring> getListAudios();
	//==============================================
	bool isOriginalSubtitleStream(int number);
	bool isOriginalAudioStream(int number);
	std::string getPathOfStream(int number);
private:
	std::map<std::string, int> hashTable;
	std::map<std::string, std::string> valueTable;
	Glib::Mutex lock;
	bool changeVideoParam;
	std::list<std::pair<int, StreamInfo> > loadedSubtitles;
	std::list<std::pair<int, StreamInfo> > loadedAudio;
	int lastNumberSubtitle;
	int lastNumberAudio;
	std::string aktualPlaySubtitlesStr;
	int aktualPlaySubtitles;
	int aktualPlayAudio;
	std::string aktualPlayAudioStr;
	bool subChanged;
	bool audChanged;
	int unknownCounter;
};

#endif /* STRINGANALYZE_H_ */
