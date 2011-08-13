/*
 * PlayerKernel.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "PlayerKernel.h"
#include <iostream>
PlayerKernel::PlayerKernel(StringAnalyze *analyze){
	playing = false;
	isPause = false;
	childPid = -1;
	stringAnalyze = analyze;
}

PlayerKernel::~PlayerKernel() {

}
void PlayerKernel::setGenerator(ScriptGenerator* gener){
	generator = gener;
}
bool PlayerKernel::play(IndigoFile* file){
	stopAnalyze = false;
	stringAnalyze->clear();
	isPause = false;
	if(childPid != -1) return false;
	childPid = -1;
	std::list<Glib::ustring> script = generator->generate(file);
	char *ll[script.size()];
	std::list<Glib::ustring>::iterator it;
	int i = 0;
	for(it = script.begin(); it != script.end(); it++){
		ll[i++] = (char*)it->c_str();
	}
	ll[i] = NULL;
	pipe(fromPlayer);
	pipe(toPlayer);
	childPid = fork();
	if(childPid == 0){	//child
		close(1);
		dup(fromPlayer[1]);
		close(fromPlayer[0]);
		close(fromPlayer[1]);
		close(toPlayer[1]);
		close(0);
		dup(toPlayer[0]);
		close(toPlayer[0]);
		execv(ll[0], ll);
		exit(0);
	}
	if(childPid > 0){
		close(fromPlayer[1]);
		close(toPlayer[0]);
		thread = Glib::Thread::create(sigc::mem_fun(*this, &PlayerKernel::listener), false);
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlayerKernel::aktualTime), 300);
		playing = true;
		return true;
	}
	return false;
}
bool PlayerKernel::aktualTime(){
	if(childPid == -1){
		return false;
	}
	if(playing)
		dprintf(toPlayer[1], "get_time_pos\n");
	return true;
}
void PlayerKernel::listener(){
	char buf[1024];
	int n = 0;
	unsigned int odsad = 0;
	std::string ss;
	int i;
	while((n = read(fromPlayer[0], buf, 1024)) > 0){
		odsad = 0;
		buf[n] = '\0';
		for(i=0; i < n; i++){
			if(buf[i] == '\n'){
				buf[i] = '\0';
				ss += std::string((buf+odsad));
				if(!stopAnalyze)
					stringAnalyze->analyze(ss);
				ss = "";
				odsad = i+1;
			}
		}
		ss += buf+odsad;
	}
	playing = false;
	childPid = -1;
}
void PlayerKernel::pause(){
	if(playing && !isPause){
		dprintf(toPlayer[1], "pause\n");
		dprintf(toPlayer[1], "osd_show_text pause\n");
		isPause = true;
	}
}
void PlayerKernel::resume(){
	if(playing && isPause){
		dprintf(toPlayer[1], "pause\n");
		dprintf(toPlayer[1], "osd_show_text resume\n");
		isPause = false;
	}
}
void PlayerKernel::stop(){
	if(!playing && childPid != -1){
		kill(childPid, 9);
		childPid = -1;
		playing = false;
	}
	if(playing){
		stopAnalyze = true;
		dprintf(toPlayer[1], "quit\n");
		playing = false;
		int status;
		wait(&status);
		childPid = -1;
	}
}
void PlayerKernel::mute(bool mut){
	if(playing){
		if(mut)
			dprintf(toPlayer[1], "mute 1\n osd_show_text mute\n");
		else
			dprintf(toPlayer[1], "mute 0\n osd_show_text unmute\n");
	}
}
void PlayerKernel::soundLevel(double level){
	if(playing){
		dprintf(toPlayer[1], "volume %lf 1\n", level);
	}
}
void PlayerKernel::changeTime(int time){
	std::cout<<time<<std::endl;
	if(playing){
		dprintf(toPlayer[1], "seek %d 2\n", time);
	}
}
bool PlayerKernel::isPlaying(){
	return playing;
}
