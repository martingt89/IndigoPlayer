/*
 * StringAnalyze.h
 *
 *  Created on: 11.8.2011
 *      Author: xgeier
 */

#ifndef STRINGANALYZE_H_
#define STRINGANALYZE_H_

#include <glibmm/dispatcher.h>
#include <string>
#include <map>

class StringAnalyze {
public:
	StringAnalyze();
	virtual ~StringAnalyze();
	void analyze(std::string);
	std::string getVariable(std::string variable);
	Glib::Dispatcher message;
	void clear();
private:
	std::map<std::string, int> hashTable;
	std::map<std::string, std::string> valueTable;
};

#endif /* STRINGANALYZE_H_ */
