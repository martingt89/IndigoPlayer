/*
 * ExclusiveLock.h
 *
 *  Created on: 27.6.2011
 *      Author: xgeier
 */

#ifndef EXCLUSIVELOCK_H_
#define EXCLUSIVELOCK_H_

#include <string>
#include <iostream>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class ExclusiveLock {
public:
	ExclusiveLock(std::string, bool);
	virtual ~ExclusiveLock();
	bool tryLockFile();
	void unlockFile();
private:
	int lockFileDescriptor;
	std::string filePath;
	bool blockMode;
};

#endif /* EXCLUSIVELOCK_H_ */
