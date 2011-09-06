/*
 * ConfigFile.cpp
 *
 *  Created on: 29.7.2011
 *      Author: xgeier
 */

#include "ConfigFile.h"
#include <iostream>


std::map<IndigoConfig::Config, std::string> ConfigFile::config;
std::map<std::string, IndigoConfig::Config> ConfigFile::stringToConfig;

ConfigFile::ConfigFile(){
	init();
}
ConfigFile::ConfigFile(bool load) {
	init();
	std::string value;
	std::string key;
	if (load) {
		std::ifstream in(CONFIG);
		if (in.is_open()) {
			std::string line;
			std::string::size_type i;
			std::string::size_type j;
			while (getline(in, line)) {
				i = line.find_first_not_of(" \t\n\v");
				if (i != std::string::npos && line[i] == '#')
					continue;
				j = line.find('=', 0);
				key = line.substr(i, j - i);
				value = line.substr(j + 1, line.length() - (j + 1));

				if(stringToConfig.find(key) != stringToConfig.end()){
					config[stringToConfig[key]] = value;
				}
			}
		}
	}
}

ConfigFile::~ConfigFile() {
	// TODO Auto-generated destructor stub
}
void ConfigFile::init(){
	if(stringToConfig.size() == 0){
		stringToConfig["subCp"] = IndigoConfig::SUBCP;
		stringToConfig["subColor"] = IndigoConfig::SUBCOLOR;
		stringToConfig["oneInstance"] = IndigoConfig::ONEINSTANCE;
		stringToConfig["mplayerPath"] = IndigoConfig::MPLAYERPATH;
		stringToConfig["audioVolume"] = IndigoConfig::AUDIOVOLUME;
	}
}
bool ConfigFile::isSet(IndigoConfig::Config name){
	return config.find(name) != config.end();
}
std::string ConfigFile::getAsString(IndigoConfig::Config name){
	return config[name];
}
bool ConfigFile::getAsBool(IndigoConfig::Config name){
	return config[name] == "true";
}
double ConfigFile::getAsDouble(IndigoConfig::Config name){
	double value = 0;
	translate << config[name];
	translate >> value;
	return value;
}
