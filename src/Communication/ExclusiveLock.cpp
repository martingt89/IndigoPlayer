/*
 * ExclusiveLock.cpp
 *
 *  Created on: 27.6.2011
 *      Author: xgeier
 */

#include "ExclusiveLock.h"

using namespace std;

ExclusiveLock::ExclusiveLock(std::string filePath, bool block=false) {
	this->filePath = filePath;
	this->blockMode = block;
	lockFileDescriptor = -1;
}

ExclusiveLock::~ExclusiveLock() {
	//remove(filePath.c_str());
}

bool ExclusiveLock::tryLockFile(){
	lockFileDescriptor = open(filePath.c_str(), O_CREAT | O_WRONLY, 0644);
	if (lockFileDescriptor >= 0) {
		cerr << "INFO: otvorili sme lock subor" << endl;
		int stat = -1;
		if(blockMode)
			stat = lockf(lockFileDescriptor, F_LOCK, 0);
		else
			stat = lockf(lockFileDescriptor, F_TLOCK, 0);
		if (stat == 0) {
			cerr << "INFO: zamkol som lock subor" << endl;
			return true;
		}
	}
	cerr << "INFO: neotvorili ani nevytvorili sme lock subor, subor je uz asi vytvoreny a zamknuty" << endl;
	return false;
}

void ExclusiveLock::unlockFile(){
	if(lockFileDescriptor >= 0)
		lockf(lockFileDescriptor, F_ULOCK, 0);
}

