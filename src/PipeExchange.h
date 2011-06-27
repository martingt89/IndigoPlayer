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

class PipeExchange {
public:
	PipeExchange(std::string name, double version);
	virtual ~PipeExchange();
	bool openWrite();
	bool openRead();
	bool tryLock();
	void writeFiles(int argc, char *argv[]);
private:
	int readPipe;
	int writePipe;
	int lock;
	std::string name;
	double version;
	std::string getTemporaryPath();
	std::string getPipeFilePath();
	std::string getSemaphoreName();
	std::string getLockFilePath();

	sem_t *mysem;
	std::string sem_name;
};

#endif /* PIPEEXCHANGE_H_ */
