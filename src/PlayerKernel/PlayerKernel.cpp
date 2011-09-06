/*
 * PlayerKernel.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "PlayerKernel.h"
#include <iostream>

PlayerKernel::PlayerKernel(MediaPackage *analyze) {
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
	if (file == NULL){
		onePlay.unlock();
		return false;
	}
	if(childPid != -1){
		onePlay.unlock();
		return false;
	}
	childPid = -1;
	pause = false;
	std::list<Glib::ustring> script = generator->generate(file, loadTime, info);
	char *ll[script.size()];
	std::list<Glib::ustring>::iterator it;
	int i = 0;
	for (it = script.begin(); it != script.end(); it++) {
		ll[i++] = (char*) it->c_str();
	}
	ll[i] = NULL;
	if (pipe(fromPlayer) == -1) {
		//LOGGING TODO
		std::cerr<<"SEVERE: Cannot creat Pipe!!!"<<std::endl;
		onePlay.unlock();
		return false;
	}
	if (pipe(toPlayer) == -1) {
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		std::cerr<<"SEVERE: Cannot creat Pipe!!!"<<std::endl;
		//LOGGING TODO
		onePlay.unlock();
		return false;
	}
	if (pipe(fromPlayerErr) == -1) {
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[0]);
		close(toPlayer[1]);
		std::cerr<<"SEVERE: Cannot creat Pipe!!!"<<std::endl;
		//LOGGING TODO
		onePlay.unlock();
		return false;
	}
	int hh[2];
	pipe(hh);
	childPid = fork();
	if(childPid == -1) {
		std::cerr<<"SEVERE: Cannot fork process!!!"<<std::endl;
		onePlay.unlock();
	}
	if (childPid == 0) { //child
		close(1);
		dup(fromPlayer[1]);
		close(0);
		dup(toPlayer[0]);
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[1]);
		close(toPlayer[0]);
		close(2);
		dup(fromPlayerErr[1]);
		close(fromPlayerErr[0]);
		close(fromPlayerErr[1]);
		execv(ll[0], ll);
		std::cerr<<"SEVERE: Cannot start MPlayer!!!"<<std::endl;
		exit(0);
	}
	if (childPid > 0) {
		std::cout<<"INFO: childPid > 0"<<std::endl;
		close(fromPlayer[1]);
		close(toPlayer[0]);
		close(fromPlayerErr[1]);
		thread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::listener), false);
		errThread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::mplayerError), true);
		if(!errThread)
			onePlay.unlock();
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlayerKernel::aktualTime), 300);
		std::cout<<"INFO: Start playing!!!"<<std::endl;
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
	std::cout<<"INFO: Starting error read"<<std::endl;
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
				std::cerr << "MPlayer Error: '" << ss << "'" << std::endl;
				ss = "";
				odsad = i + 1;
			}
		}
		ss += buf + odsad;
	}
	close(fromPlayerErr[0]);
	onePlay.unlock();
	std::cout<<"INFO: Closing error read"<<std::endl;
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
	playing = false;
	childPid = -1;
	errThread->join();
}

void PlayerKernel::stop() {
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
//		std::cout<<"COMMAND: "<<command<<std::endl;
		if(pause)
			dprintf(toPlayer[1], "%s %s", "pausing",command.c_str());
		else
			dprintf(toPlayer[1], "%s", command.c_str());
	}
}
