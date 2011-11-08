/*
 * OneInstance.h
 *
 *  Created on: 28.10.2011
 *      Author: martin89
 */

#ifndef ONEINSTANCE_H_
#define ONEINSTANCE_H_

#include "Player/IndigoPlayer.h"
#include "Files/FileUtilities.h"
#include "Files/PathLoader.h"
#include "Files/Logger.h"
#include <mqueue.h>
#include <errno.h>

class OneInstance {
private:
	IndigoPlayer *player;
	void run();
	Glib::Thread *thr;
	int pipeFd;
	int instanceFd;
	bool stopReading;
	PathLoader pathLoader;
	IndigoLogger::Logger log;
public:
	OneInstance(IndigoPlayer *_player);
	bool lockInstance(bool &pipe);
	void unlockInstance();
	bool start(std::list<IndigoFile*> files);
	void join();
	void closeMQueue();
};

#endif /* ONEINSTANCE_H_ */
