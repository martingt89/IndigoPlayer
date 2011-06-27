/*
 * Configuration.h
 *
 *  Created on: 24.6.2011
 *      Author: xgeier
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

class Configuration {
public:
	Configuration(std::string name, double version);
	virtual ~Configuration();
	bool onlyOne();
};

#endif /* CONFIGURATION_H_ */
