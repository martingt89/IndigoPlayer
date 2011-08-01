/**
 * Zavysle na platforme linux, pre prepis na iny system bude treba tu zamakt
 */

#ifndef PIPEEXCHANGE_H_
#define PIPEEXCHANGE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <errno.h>

#include "ExclusiveLock.h"
#include "../ProgramUtilitys.h"

class PipeExchange {
public:
	PipeExchange(std::string name, double version);
	virtual ~PipeExchange();
	bool createPipe();
	void removePipe();
	std::string readMessage();
	bool writeFiles(int argc, char *argv[]);
private:
	int readPipe;
	int writePipe;
	std::string name;
	double version;
	ProgramUtilitys util;
};

#endif /* PIPEEXCHANGE_H_ */
