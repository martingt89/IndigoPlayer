/*
 * ProgramUtilitys.cpp
 *
 *  Created on: 27.6.2011
 *      Author: xgeier
 */

#include "ProgramUtilitys.h"
#include "../Settings.h"

std::string ProgramUtilitys::getInstanceLockFilePath() {
	std::stringstream ostr;
	ostr << getTemporaryPath();
	ostr << NAME;
	ostr << VERSION;
	ostr << "instanceLock";
	return ostr.str();
}
std::string ProgramUtilitys::getPipeFilePath() {
	std::stringstream ostr;
	ostr << getTemporaryPath();
	ostr << NAME;
	ostr << VERSION;
	ostr << "pipe";
	return ostr.str();
}
std::string ProgramUtilitys::getPipeLockFilePath() {
	std::stringstream ostr;
	ostr << getTemporaryPath();
	ostr << NAME;
	ostr << VERSION;
	ostr << "pipelock";
	return ostr.str();
}
std::string ProgramUtilitys::getTemporaryPath() {
	const char *dir = getenv("TMPDIR");
	if (!dir) {
		dir = getenv("TMP");
		if (!dir) {
			dir = getenv("TEMP");
			if (!dir) {
				dir = "/tmp";
			}
		}
	}
	std::string path(dir);
	if (path[path.length()] != '/') {
		path += '/';
	}
	return path;
}
