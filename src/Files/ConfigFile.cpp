/*
 * ConfigFile.cpp
 *
 *  Created on: 29.7.2011
 *      Author: xgeier
 */

#include "ConfigFile.h"

std::map<std::string, std::string> ConfigFile::config;
ConfigFile::ConfigFile(){

}
ConfigFile::ConfigFile(bool load) {
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
				config[line.substr(i, j - i)] = line.substr(j + 1, line.length() - (j + 1));
				std::cout << line.substr(i, j - i) << " " << line.substr(j + 1, line.length() - (j + 1))
						<< std::endl;
			}
		}
	}
}

ConfigFile::~ConfigFile() {
	// TODO Auto-generated destructor stub
}

bool ConfigFile::isOneInstance() {
	return config["oneInstace"] == "true";
}
std::string ConfigFile::getSubCp() {
	return config["subCp"];
}
std::string ConfigFile::getSubColor() {
	return config["subColor"];
}
