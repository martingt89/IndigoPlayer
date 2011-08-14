/*
 * ConfigFile.h
 *
 *  Created on: 29.7.2011
 *      Author: xgeier
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#include <map>
#include "../../Settings.h"
#include <iostream>
#include <fstream>
#include <string>

class ConfigFile {
public:
	ConfigFile();
	ConfigFile(bool load);
	virtual ~ConfigFile();
	bool isOneInstance();
	std::string getSubCp();
	std::string getSubColor();
private:
	static std::map<std::string, std::string> config;
};

#endif /* CONFIGFILE_H_ */
