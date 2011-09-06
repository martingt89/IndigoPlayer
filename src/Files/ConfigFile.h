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
#include <fstream>
#include <string>
#include <sstream>

namespace IndigoConfig{
	enum Config{
		SUBCP,
		SUBCOLOR,
		ONEINSTANCE,
		MPLAYERPATH,
		AUDIOVOLUME
	};
}

class ConfigFile {
public:
	ConfigFile();
	ConfigFile(bool load);
	virtual ~ConfigFile();
//	bool isOneInstance();
//	std::string getSubCp();
//	std::string getSubColor();

	bool isSet(IndigoConfig::Config name);
	std::string getAsString(IndigoConfig::Config name);
	bool getAsBool(IndigoConfig::Config name);
	double getAsDouble(IndigoConfig::Config name);
private:
	void init();
	std::stringstream translate;
	static std::map<IndigoConfig::Config, std::string> config;
	static std::map<std::string, IndigoConfig::Config> stringToConfig;
};

#endif /* CONFIGFILE_H_ */
