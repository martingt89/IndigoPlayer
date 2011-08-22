/*
 * PlayerKernel.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "PlayerKernel.h"
#include <iostream>

PlayerKernel::PlayerKernel(MediaPackage *analyze) {
	setInfo = false;
	playing = false;
	save = false;
	childPid = -1;
	stringAnalyze = analyze;
	isAlive = false;
	lastSetFile = NULL;
	chapter = 0;
}

PlayerKernel::~PlayerKernel() {

}
void PlayerKernel::setGenerator(ScriptGenerator* gener) {
	generator = gener;
}

bool PlayerKernel::playChapter(int chap) {
	int loadSave = false;
	playing = false;
	if (chapter != chap)
		save = false;
	chapter = chap;
	if (save) {
//		std::cout<<"saved "<<savedData.getPosition()<<std::endl;
		loadSave = true;
		save = false;
	}
	stringAnalyze->clear();
	if (!isAlive) {
		return false;
	}
	if (lastSetFile == NULL
		)
		return false;
	childPid = -1;
	if (chapter > 0 && setInfo == false) {
		return false;
	}
	std::list<Glib::ustring> script = generator->generate(lastSetFile, loadSave, savedData);
	char *ll[script.size()];std
	::list<Glib::ustring>::iterator it;
	int i = 0;
	for (it = script.begin(); it != script.end(); it++) {
		ll[i++] = (char*) it->c_str();
	}
	ll[i] = NULL;
	if (pipe(fromPlayer) == -1) {
		//LOGGING TODO
		return false;
	}
	if (pipe(toPlayer) == -1) {
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		//LOGGING TODO
		return false;
	}
	if (pipe(fromPlayerErr) == -1) {
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[0]);
		close(toPlayer[1]);
		//LOGGING TODO
		return false;
	}
	childPid = fork();
	if (childPid == 0) { //child
		close(1);
		dup(fromPlayer[1]);
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[1]);
		close(0);
		dup(toPlayer[0]);
		close(toPlayer[0]);
		close(2);
		dup(fromPlayerErr[1]);
		close(fromPlayerErr[0]);
		close(fromPlayerErr[1]);
		execv(ll[0], ll);
		exit(0);
	}
	if (childPid > 0) {
		close(fromPlayer[1]);
		close(toPlayer[0]);
		close(fromPlayerErr[1]);
		thread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::listener), false);
		errThread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::mplayerError), false);
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlayerKernel::aktualTime), 300);
		return true;
	}
	return true;
}
void PlayerKernel::playNextChapter() {
	if (isAlive) {
		if (!save)
			if (playChapter(++chapter) == false)
				endPlaying();
		if (save)
			if (playChapter(chapter) == false)
				endPlaying();
	}
}
void PlayerKernel::endPlaying() {
	isAlive = false;
	stringAnalyze->quitPlay();
}
bool PlayerKernel::play(IndigoFile* file) {
	chapter = 0;
	setInfo = false;
	save = false;
	if (isAlive == true)
		return false;
	isAlive = true;
	lastSetFile = file;
	if (playChapter(chapter) == false) {
		endPlaying();
		return false;
	}
	return true;
}
bool PlayerKernel::aktualTime() {
	if (isAlive == false) {
		return false;
	}
	if (playing)
		dprintf(toPlayer[1], "get_time_pos\n");
	return true;
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
				std::cerr << "MPlayer Error: '" << ss << "'" << std::endl;
				ss = "";
				odsad = i + 1;
			}
		}
		ss += buf + odsad;
	}
	close(fromPlayerErr[0]);
}
void PlayerKernel::listener() {
	char buf[1024];
	int n = 0;
	unsigned int odsad = 0;
	std::string ss;
	int i;
	int stat = 0;
	while ((n = read(fromPlayer[0], buf, 1024)) > 0) {
		odsad = 0;
		buf[n] = '\0';
		for (i = 0; i < n; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				ss += std::string((buf + odsad));
				stat = stringAnalyze->analyze(ss);
				if (stat == 1) {
					playing = true;
				}
				if (stat == 2)
					playing = false;
				ss = "";
				odsad = i + 1;
			}
		}
		ss += buf + odsad;
	}
	close(fromPlayer[0]);
	playing = false;
	childPid = -1;
	playNextChapter();
}

void PlayerKernel::stop() {
	int pid = childPid;
	isAlive = false;
	if (!playing && pid != -1) {
		kill(pid, 9);
		playing = false;
		endPlaying();
	}
	if (playing) {
		dprintf(toPlayer[1], "quit\n");
		playing = false;
		int status;
		wait(&status);
		childPid = -1;
		endPlaying();
	}
}

void PlayerKernel::sendCommand(Glib::ustring command) {
	if (playing) {
		dprintf(toPlayer[1], "%s", command.c_str());
	}
}

bool PlayerKernel::isPlaying() {
	return isAlive;
}

void PlayerKernel::rebootPlay() {
	if (isPlaying()) {
		aktualTime();
		save = true;
		savedData = stringAnalyze->getSavedData();
		dprintf(toPlayer[1], "quit\n");
		playing = false;
		int status;
		wait(&status);
		childPid = -1;
	}
}
