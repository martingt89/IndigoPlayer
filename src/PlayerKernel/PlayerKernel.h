/*
 * PlayerKernel.h
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#ifndef PLAYERKERNEL_H_
#define PLAYERKERNEL_H_

#include "ScriptGenerator.h"
#include "MediaPackage.h"
#include <glibmm/ustring.h>
#include <glibmm/thread.h>
#include <list>
#include <iterator>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sys/types.h>
#include <signal.h>
#include <cstdlib>
#include "../Files/IndigoFile.h"
#include "../Player/SavedFileInfo.h"
#include "../Files/Logger.h"
#include "../Settings.h"

class PlayerKernel {
public:
	PlayerKernel(MediaPackage*);
	virtual ~PlayerKernel();
	bool play(IndigoFile* file, bool loadTime=false, SavedFileInfo* info=NULL);
	void setGenerator(ScriptGenerator* gener);
	bool isPlaying();
	void stop();
	void sendCommand(Glib::ustring command);
	void pausePlayer();
private:
	bool playMe(IndigoFile* file, bool loadTime, SavedFileInfo* info);
	void listener();
	void mplayerError();
	bool aktualTime();
	ScriptGenerator* generator;
	MediaPackage* stringAnalyze;
	Glib::Thread* thread;
	Glib::Thread* errThread;
	Glib::Mutex onePlay;

	IndigoLogger::Logger logging;
	IndigoLogger::Logger mLogging;

	bool playing;
	int fromPlayerErr[2];
	int fromPlayer[2];
	int toPlayer[2];
	int childPid;
	bool pause;
};

#endif /* PLAYERKERNEL_H_ */
