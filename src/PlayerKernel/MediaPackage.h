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
	void analyzeErrors(Glib::ustring text);
	void sendExit();
	std::string getVariable(std::string variable);
	int getVariableAsInteger(std::string variable);
	Glib::Dispatcher message;
	//------------------------------------------------
	void clear();
	void quitPlay();

	int getSubtitleNumberFromName(std::string path);
	int getAudioNumberFromName(std::string text);

	bool isStart(bool off=true);
	bool isEnd(bool off=true);
	bool isVideoParamChange();
	bool isSubtitleChanged();
	bool isAudioChanged();
	bool isVideoChanged();

	std::list<Glib::ustring> getListSubtitles();
	std::list<Glib::ustring> getListAudios();
	//==============================================
	bool isOriginalAudioStream(int number);
	bool isOriginalSubtitleFromName(Glib::ustring name);
	//==============================================
	Glib::ustring getSubtitleNameFromNumber(int number, bool orig);
	Glib::ustring getAudioNameFromNumber(int number);
private:
	std::map<std::string, int> hashTable;
	std::map<std::string, std::string> valueTable;
	Glib::Mutex lock;

	std::list<std::pair<int, StreamInfo> > loadedSubtitles;
	std::list<std::pair<int, StreamInfo> > loadedAudio;
	int lastNumberSubtitle;
	int lastNumberAudio;

	bool subChanged;
	bool audChanged;
	bool changeVideoParam;
	int unknownCounter;

	bool start;
	bool end;
	bool firstEnd;
};

#endif /* STRINGANALYZE_H_ */
