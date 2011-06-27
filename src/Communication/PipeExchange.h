/**
 * Zavysle na platforme linux, pre prepis na iny system bude treba tu zamakt
 */

#ifndef PIPEEXCHANGE_H_
#define PIPEEXCHANGE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>

#include "../ProgramUtilitys.h"

class PipeExchange {
public:
	PipeExchange(std::string name, double version);
	virtual ~PipeExchange();
	bool openWrite();
	bool openRead();
	bool createPipe();
	void removePipe();
	std::string readCommand();
	void writeFiles(int argc, char *argv[]);
private:
	int readPipe;
	int writePipe;
	std::string name;
	double version;
	ProgramUtilitys util;
};

#endif /* PIPEEXCHANGE_H_ */
