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

ConfigFile::ConfigFile() {
	init();
	if (config.size() == 0) {
		initDefaultValues();
		std::string value;
		std::string key;
		//std::string file = getMainFolder() + CONFIG;
		std::string file = pathLoader.getConfigFilePath();
		std::ifstream in(file.c_str());
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
				if(value.size()!=0)
					if(stringToConfig.find(key) != stringToConfig.end())
						config[stringToConfig[key]] = value;
			}
		}
	}
}

ConfigFile::~ConfigFile() {
}
void ConfigFile::init(){
	if(stringToConfig.size() == 0){
		stringToConfig["logPath"] = IndigoConfig::LOGPATH;
		stringToConfig["logFileName"] = IndigoConfig::LOGFILENAME;
		stringToConfig["subCp"] = IndigoConfig::SUBCP;
		stringToConfig["subColor"] = IndigoConfig::SUBCOLOR;
		stringToConfig["oneInstance"] = IndigoConfig::ONEINSTANCE;
		stringToConfig["mplayerPath"] = IndigoConfig::MPLAYERPATH;
		stringToConfig["audioVolume"] = IndigoConfig::AUDIOVOLUME;
		stringToConfig["audioOutput"] = IndigoConfig::AUDIOOUTPUT;
	}
}
void ConfigFile::saveToFile(){
	std::ofstream out(pathLoader.getConfigFilePath().c_str());
	std::map<std::string, IndigoConfig::Config>::iterator it;
	for(it = stringToConfig.begin(); it != stringToConfig.end(); it++){
		out<<it->first<<"="<<config[it->second]<<std::endl;
	}
	out.close();
}
void ConfigFile::initDefaultValues(){
	//config[IndigoConfig::LOGPATH] = getMainFolder()+LOGFOLDER+"/";
	config[IndigoConfig::LOGPATH] = pathLoader.getLogFolder();
	config[IndigoConfig::LOGFILENAME] = "player.log";
	config[IndigoConfig::MPLAYERPATH] = "/usr/bin/mplayer";
}
void ConfigFile::set(IndigoConfig::Config name, Glib::ustring value){
	config[name] = value;
}

void ConfigFile::set(IndigoConfig::Config name, double value){
	config[name] = Glib::ustring::format(value);
}
void ConfigFile::set(IndigoConfig::Config name, bool value){
	if(value)
		config[name] = "true";
	else
		config[name] = "false";
}

bool ConfigFile::get(IndigoConfig::Config name, Glib::ustring &strin){
	strin = "";
	if(config.find(name) != config.end()){
		strin = config[name];
		if(strin.size() == 0) return false;
		return true;
	}
	return false;
}
bool ConfigFile::get(IndigoConfig::Config name, bool &boole){
	boole = false;
	if(config.find(name) != config.end()){
		boole = config[name] == "true";
		return true;
	}
	return false;
}
bool ConfigFile::get(IndigoConfig::Config name, double &doubl){
	doubl = 0;
	if(config.find(name) != config.end()){
		translate << config[name];
		translate >> doubl;
		if(config[name].size() == 0) return false;
		return true;
	}
	return false;
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
