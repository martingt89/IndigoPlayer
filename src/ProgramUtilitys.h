/*
 * ProgramUtilitys.h
 *
 *  Created on: 27.6.2011
 *      Author: xgeier
 */

#ifndef PROGRAMUTILITYS_H_
#define PROGRAMUTILITYS_H_

#include <string>
#include <sstream>
#include <cstdlib>

class ProgramUtilitys {
public:
	std::string getInstanceLockFilePath();
	std::string getPipeFilePath();
	std::string getPipeLockFilePath();
private:
	std::string getTemporaryPath();
};

#endif /* PROGRAMUTILITYS_H_ */
