/*
 * PlayerKernel.h
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#ifndef PLAYERKERNEL_H_
#define PLAYERKERNEL_H_

#include "../../Settings.h"
#include "ScriptGenerator.h"
#include "../Files/IndigoFile.h"
#include "StringAnalyze.h"
#include <glibmm/ustring.h>
#include <glibmm/thread.h>
#include <list>
#include <iterator>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

class PlayerKernel {
public:
	PlayerKernel(StringAnalyze*);
	virtual ~PlayerKernel();
	void play(IndigoFile* file);
	void setGenerator(ScriptGenerator* gener);
	bool isPlaying();
	void pause();
	void resume();
	void stop();
	void mute(bool mut);
	void soundLevel(double level);
	void changeTime(int time);
private:
	void listener();
	bool aktualTime();
	ScriptGenerator* generator;
	StringAnalyze* stringAnalyze;
	Glib::Thread* thread;
	bool playing;
	bool isPause;
	int fromPlayer[2];
	int toPlayer[2];
	int childPid;
};

#endif /* PLAYERKERNEL_H_ */
