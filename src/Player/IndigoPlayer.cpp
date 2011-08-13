/*
 * Player.cpp
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#include "IndigoPlayer.h"
#include <iostream>
#include <giomm/file.h>

IndigoPlayer::IndigoPlayer(PlayerWindow *playerWin) {
	playerWindow = playerWin;
	playerWindow->setListener(this);
	mediaPackage = new StringAnalyze();
	kernel = new PlayerKernel(mediaPackage);
	generator = new ScriptGenerator();
	mediaPackage->message.connect(sigc::mem_fun(this, &IndigoPlayer::messageIncomming));
}
void IndigoPlayer::setPlaylist(Playlist *playlist) {
	this->playlist = playlist;
	this->playlist->setListener(this);
}
void IndigoPlayer::setVideoBoard(VideoBoard* board) {
	this->videoBoard = board;
	generator->setVideoBoard(videoBoard);
}
void IndigoPlayer::setControlPanel(ControlPanel* control){
	controlPanel = control;
	controlPanel->setListener(this);
	generator->setControlPanel(controlPanel);
}
void IndigoPlayer::setOpenDialog(OpenFileDialog* dialog) {
	openDialog = dialog;
	openDialog->setListener(this);
}

void IndigoPlayer::messageIncomming(){
	if(mediaPackage->getVariable("ID_LENGTH").size() != 0){
		std::stringstream ss;
		ss << mediaPackage->getVariable("ID_LENGTH");
		int duration = 0;
		ss >> duration;
		controlPanel->setDuration(duration);
	}
	if(mediaPackage->getVariable("ANS_TIME_POSITION").size() != 0){
		std::stringstream ss;
		ss << mediaPackage->getVariable("ANS_TIME_POSITION");
		double position = 0;
		ss >> position;
		controlPanel->setPosition((int)position);
	}
	if(mediaPackage->getVariable("ID_EXIT").size() != 0){
		clearPlaying();
		clickForward();
	}
}

void IndigoPlayer::addFiles(std::list<IndigoFile*> files, bool play) {
	playlist->addFiles(files);
	if (play) {
		this->stopPlayer();
		playlist->jumpToLastAdd();
		this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickPlaylistBoard(){
	this->stopPlayer();
	if(playlist->aktualizeFile())
		this->playFile(playlist->getFile());
}
void IndigoPlayer::stopPlayer() {
	kernel->stop();
	this->clearPlaying();
}
void IndigoPlayer::playFile(IndigoFile* file) {
	if(file != NULL){
		kernel->setGenerator(generator);
		videoBoard->showLogo(false);
		if(kernel->play(file)){
			controlPanel->pushPlayButton();
			playerWindow->setWindowTitle(file->getName());
		}else{
			//asi nejake logy
		}
	}
}
void IndigoPlayer::clickPlay() {
	if(!kernel->isPlaying()){
		if (playlist->isEmpty()) {
			openDialog->show();
			controlPanel->popPlayButton();
			return;
		}
		this->stopPlayer();
		IndigoFile* file = playlist->getFile();
		if(file == NULL){
			//std::cout<<"Neser ma"<<std::endl;
			openDialog->show();
			//controlPanel->popPlayButton();
		}else{
			this->playFile(file);
		}
	}else{
		kernel->resume();
	}
}
void IndigoPlayer::clickPause() {
	kernel->pause();
}
void IndigoPlayer::clickForward() {
	if(true){
		this->stopPlayer();
		if(playlist->goNextFile())
			this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickBackward() {
	if(true){
		this->stopPlayer();
		if(playlist->goPrevioseFile())
			this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickCancel() {
	this->stopPlayer();
}
void IndigoPlayer::clearPlaying(){
	videoBoard->showLogo(true);
	controlPanel->popPlayButton();
	controlPanel->clearTime();
	playerWindow->setWindowTitle("");
}
void IndigoPlayer::clickThisOptions() {
	//teraz neriesit
}
void IndigoPlayer::clickKill() {
	//teraz neriesit
}
void IndigoPlayer::clickOpen() {
	openDialog->show();
}
void IndigoPlayer::clickRewind() {
	this->stopPlayer();
	this->playFile(playlist->getFile());
}
void IndigoPlayer::clickMute() {
	kernel->mute(true);
}
void IndigoPlayer::clickSound() {
	kernel->soundLevel(controlPanel->getAudioLevel());
	kernel->mute(false);
}
void IndigoPlayer::changeTimeLine() {
	kernel->changeTime(controlPanel->getTime());
}
void IndigoPlayer::changeSoundLevel() {
	kernel->soundLevel(controlPanel->getAudioLevel());
}
void IndigoPlayer::quit(){
	kernel->stop();
	Gtk::Main::quit();
}
IndigoPlayer::~IndigoPlayer() {
	delete mediaPackage;
	delete kernel;
	delete generator;
}
