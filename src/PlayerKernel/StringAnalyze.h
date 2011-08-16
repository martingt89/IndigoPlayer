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

class StringAnalyze {
public:
	StringAnalyze();
	virtual ~StringAnalyze();
	int analyze(std::string);
	std::string getVariable(std::string variable);
	Glib::Dispatcher message;
	void clear();
	void quitPlay();
	SavedData getSavedData();
private:
	std::map<std::string, int> hashTable;
	std::map<std::string, std::string> valueTable;
	Glib::Mutex lock;
};

#endif /* STRINGANALYZE_H_ */
