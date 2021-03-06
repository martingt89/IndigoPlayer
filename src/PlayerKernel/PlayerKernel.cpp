/*
 * PlayerKernel.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "PlayerKernel.h"
#include <iostream>

PlayerKernel::PlayerKernel(MediaPackage *analyze): mLogging("M") {
	playing = false;
	childPid = -1;
	stringAnalyze = analyze;
}

PlayerKernel::~PlayerKernel() {

}

void PlayerKernel::setGenerator(ScriptGenerator* gener) {
	generator = gener;
}
void PlayerKernel::pausePlayer(){
	pause = !pause;
}
bool PlayerKernel::play(IndigoFile* file, bool loadTime, SavedFileInfo* info) {
	onePlay.lock();
	bool me = playMe(file, loadTime, info);
	if(me == false)
		onePlay.unlock();
	return me;
}
bool PlayerKernel::playMe(IndigoFile* file, bool loadTime, SavedFileInfo* info) {
	logging.log(IndigoLogger::DEBUG, "PlayerKernel::play, play file");
	if (file == NULL){
		logging.log(IndigoLogger::ALERT, "PlayerKernel::play, IndigoFile* musn't be NULL");
		return false;
	}
	if(childPid != -1){
		logging.log(IndigoLogger::ALERT, "PlayerKernel::play, playback not end");
		return false;
	}
	childPid = -1;
	pause = false;
	std::list<Glib::ustring> script = generator->generate(file, loadTime, info);
	if(script.size() == 0){
		logging.log(IndigoLogger::CRIT, "PlayerKernel::play, no script to run");
		return false;
	}
	char *ll[script.size()];
	std::list<Glib::ustring>::iterator it;
	int i = 0;
	Glib::ustring scr = "";
	for (it = script.begin(); it != script.end(); it++) {
		ll[i++] = (char*) it->c_str();
		scr += *it+" ";
	}
	mLogging.log(IndigoLogger::INFO, scr);
	ll[i] = NULL;
	if (pipe(fromPlayer) == -1) {
		logging.log(IndigoLogger::CRIT, "PlayerKernel::play, pipe 'fromPlayer' not created");
		return false;
	}
	if (pipe(toPlayer) == -1) {
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		logging.log(IndigoLogger::CRIT, "PlayerKernel::play, pipe 'toPlayer' not created");
		return false;
	}
	if (pipe(fromPlayerErr) == -1) {
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[0]);
		close(toPlayer[1]);
		logging.log(IndigoLogger::CRIT, "PlayerKernel::play, pipe 'fromPlayerErr' not created");
		return false;
	}
	childPid = fork();
	if(childPid == -1) {
		logging.log(IndigoLogger::CRIT, "PlayerKernel::play, cannot fork");
		return false;
	}
	if (childPid == 0) { //child
		close(1);
		if(dup(fromPlayer[1]) == -1){
			std::cerr<<"Cannot dup mplayer input stream"<<std::endl;
		}
		close(0);
		if(dup(toPlayer[0]) == -1){
			std::cerr<<"Cannot dup mplayer output stream"<<std::endl;
		}
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[1]);
		close(toPlayer[0]);
		close(2);
		if(dup(fromPlayerErr[1]) == -1){
			std::cerr<<"Cannot dup mplayer error stream"<<std::endl;
		}
		close(fromPlayerErr[0]);
		close(fromPlayerErr[1]);
		execv(ll[0], ll);
		std::cerr<<"Cannot start mplayer"<<std::endl;
		exit(0);
	}
	if (childPid > 0) {
		close(fromPlayer[1]);
		close(toPlayer[0]);
		close(fromPlayerErr[1]);
		thread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::listener), false);
		if(!thread)
			logging.log(IndigoLogger::ALERT, "PlayerKernel::play, cannot create listener thred");
		errThread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::mplayerError), true);
		if(!errThread){
			logging.log(IndigoLogger::ALERT, "PlayerKernel::play, cannot create error thred, turn off sinc");
			onePlay.unlock();
		}
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlayerKernel::aktualTime), 300);
		playing = true;
		return true;
	}
	return true;
}

bool PlayerKernel::isPlaying(){
	return playing;
}

bool PlayerKernel::aktualTime(){
	if(playing){
		if(!pause)
			this->sendCommand("get_time_pos \n");
		return true;
	}
	return false;
}

void PlayerKernel::mplayerError() {
	char buf[1024];
	int n = 0, odsad = 0, i = 0;
	std::string ss = "";
	while ((n = read(fromPlayerErr[0], buf, 1024)) > 0) {
		odsad = 0;
		buf[n] = '\0';
		for (i = 0; i < n; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				ss += std::string((buf + odsad));
				mLogging.log(IndigoLogger::NOTICE, ss);
				ss = "";
				odsad = i + 1;
			}
		}
		ss += buf + odsad;
	}
	close(fromPlayerErr[0]);
	logging.log(IndigoLogger::DEBUG, "PlayerKernel::mplayerError, ending error thread = mplayer turn off");
	onePlay.unlock();
}
void PlayerKernel::listener() {
	char buf[1024];
	int n = 0;
	unsigned int odsad = 0;
	std::string ss;
	int i;
	while ((n = read(fromPlayer[0], buf, 1024)) > 0) {
		odsad = 0;
		buf[n] = '\0';
		for (i = 0; i < n; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				ss += std::string((buf + odsad));
				stringAnalyze->analyze(ss);
				ss = "";
				odsad = i + 1;
			}
		}
		ss += buf + odsad;
	}
	close(fromPlayer[0]);
	stringAnalyze->sendExit();
	playing = false;
	childPid = -1;
	errThread->join();
}

void PlayerKernel::stop() {
	if(childPid == -1) return;
	logging.log(IndigoLogger::DEBUG, "PlayerKernel::stop, force stop mplayer");
	int pid = childPid;
	if (!playing && pid != -1) {
		kill(pid, 9);
		playing = false;
	}
	if (playing) {
		dprintf(toPlayer[1], "quit\n");
		playing = false;
		int status;
		wait(&status);
		childPid = -1;
	}
}

void PlayerKernel::sendCommand(Glib::ustring command) {
	if (playing) {
		if(pause)
			dprintf(toPlayer[1], "%s %s", "pausing",command.c_str());
		else
			dprintf(toPlayer[1], "%s", command.c_str());
	}
}
