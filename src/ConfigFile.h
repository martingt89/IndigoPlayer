/*
 * ConfigFile.h
 *
 *  Created on: 29.7.2011
 *      Author: xgeier
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#include <map>
#include <fstream>
#include <sstream>
#include <glibmm/ustring.h>
#include <glibmm/miscutils.h>
#include "Settings.h"

namespace IndigoConfig{
	enum Config{
		LOGPATH,
		LOGFILENAME,
		SUBCP,
		SUBCOLOR,
		ONEINSTANCE,
		MPLAYERPATH,
		AUDIOVOLUME,
		AUDIOOUTPUT
	};
}

class ConfigFile {
public:
	ConfigFile();
	virtual ~ConfigFile();
	bool get(IndigoConfig::Config name, Glib::ustring &strin);
	bool get(IndigoConfig::Config name, bool &boole);
	bool get(IndigoConfig::Config name, double &doubl);

	bool isSet(IndigoConfig::Config name);
	std::string getAsString(IndigoConfig::Config name);
	bool getAsBool(IndigoConfig::Config name);
	double getAsDouble(IndigoConfig::Config name);
private:
	void init();
	void initDefaultValues();
	std::string getMainFolder();
	std::stringstream translate;
	static std::map<IndigoConfig::Config, std::string> config;
	static std::map<std::string, IndigoConfig::Config> stringToConfig;
};

#endif /* CONFIGFILE_H_ */
