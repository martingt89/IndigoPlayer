/*
 * Player.cpp
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#include "IndigoPlayer.h"
#include <iostream>
#include <giomm/file.h>

IndigoPlayer::IndigoPlayer(PlayerWindow *playerWin, OneFilePlayer* player) {
	playerWindow = playerWin;
	playerWindow->setListener(this);
	generator = new ScriptGenerator();
	filePlayer = player;
	filePlayer->setGenerator(generator);
	filePlayer->setGraphicPointer(this);
	nextFile = NULL;
	playing = false;
	stopPlay = true;
}
void IndigoPlayer::setPlaylist(Playlist *playlist) {
	this->playlist = playlist;
	this->playlist->setListener(this);
}
void IndigoPlayer::setVideoBoard(VideoBoard* board) {
	this->videoBoard = board;
	generator->setVideoBoard(videoBoard);
}
void IndigoPlayer::setControlPanel(ControlPanel* control) {
	controlPanel = control;
	controlPanel->setListener(this);
	generator->setControlPanel(controlPanel);
	if(config.isSet(IndigoConfig::AUDIOVOLUME)){
		controlPanel->setAudioLevel(config.getAsDouble(IndigoConfig::AUDIOVOLUME));
	}
}
void IndigoPlayer::setOpenDialog(OpenFileDialog* dialog) {
	openDialog = dialog;
	openDialog->setListener(this);
}
void IndigoPlayer::setThisOptions(ThisOptions* opt) {
	thisOptions = opt;
	thisOptions->setColorsPointer(filePlayer->getColorSettings());
	thisOptions->setFiltersPointer(filePlayer);
	thisOptions->stopPlaying();
}
void IndigoPlayer::setThisOptionsLoad(ThisOptionsLoad* optLoad) {
	thisOptionsLoad = optLoad;
	thisOptionsLoad->setListener(this);
}
//=====================================================================
//=====================================================================
void IndigoPlayer::incommingMessage(GraphicData data) {
	if (data.isStart()) {
		playing = true;
		thisOptions->runPlaying();
		thisOptionsLoad->runPlaying();
		controlPanel->hideLoading();
	}
	if (data.isLenght())
		controlPanel->setDuration(data.getLenght());
	if (data.isAktualTime())
		controlPanel->setPosition(data.getAktualTime());
	if (data.isResolution()) {
		int w = 0;
		int h = 0;
		data.getResolution(&w, &h);
		videoBoard->setVideoResolution(w, h, false);
	}
	if (data.isEnd()) {
		clearPlaying();
		playNextFile();
	}
	if(data.isSubtitle()){
		thisOptionsLoad->addSubtitleList(data.getSubtitleList(), false);
	}
	if(data.isAudio()){
		thisOptionsLoad->addAudioList(data.getAudioList(), false);
	}
	if(data.isAktualAudio()){
		thisOptionsLoad->setAktualAudio(data.getAktualAudio());
	}
	if(data.isAktualSubtitle()){
		thisOptionsLoad->setAktualSubtitles(data.getAktualSubtitle());
	}
}
void IndigoPlayer::playNextFile(){
	if(nextFile == NULL){
		if(!stopPlay){
			clickForwardSoftware();
		}
	}
	if(nextFile == NULL)
		playing = false;
	if(nextFile != NULL){
		filePlayer->playFile(nextFile);
		videoBoard->startPlay();
		playerWindow->setWindowTitle(nextFile->getName());
		controlPanel->showLoading();
		nextFile = NULL;
	}
}
void IndigoPlayer::clickForwardSoftware(){
	if (playlist->goNextFile())
		this->playFile(playlist->getFile());
}
void IndigoPlayer::addSubtitle(Glib::ustring file) {
	if (playing) {
		thisOptionsLoad->addSubtitles(file, true);
		playSubtitles(file);
	}
}
void IndigoPlayer::playSubtitles(Glib::ustring sub) {
	if (sub.size() > 0) {
		filePlayer->playSubtitles(sub);
	} else {
		filePlayer->hideSubtitles();
	}
}
void IndigoPlayer::playAudio(Glib::ustring name) {
	if (name.size() > 0) {
		filePlayer->playSound(name);
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
void IndigoPlayer::clickPlaylistBoard() {
	this->stopPlayer();
	if (playlist->aktualizeFile())
		this->playFile(playlist->getFile());
}
void IndigoPlayer::stopPlayer() {
	stopPlay = true;
	if (playing){
		filePlayer->stopPlayFile();
	}
	this->clearPlaying();
}
void IndigoPlayer::playFile(IndigoFile* file) {
	if (file != NULL) {
		if(!playing){
			stopPlay = false;
			nextFile = file;
			playNextFile();
			controlPanel->pushPlayButton();
		}else{
			stopPlay = false;
			nextFile = file;
		}
	}
}
void IndigoPlayer::clickPlay() {
	if (!playing) {
		if (playlist->isEmpty()) {
			openDialog->show();
			controlPanel->popPlayButton();
			return;
		}
		this->stopPlayer();
		IndigoFile* file = playlist->getFile();
		if (file == NULL) {
			openDialog->show();
			controlPanel->popPlayButton();
		} else {
			this->playFile(file);
		}
	} else {
		filePlayer->pausePlayFile();
	}
}
void IndigoPlayer::clickPause() {
	if (playing)
		filePlayer->pausePlayFile();
}
void IndigoPlayer::clickForward() {
	if (true) {
		this->stopPlayer();
		if (playlist->goNextFile())
			this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickBackward() {
	if (true) {
		this->stopPlayer();
		if (playlist->goPrevioseFile())
			this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickCancel() {
	this->stopPlayer();
}
void IndigoPlayer::clearPlaying() {
	videoBoard->stopPlay();
	controlPanel->popPlayButton();
	controlPanel->clearTime();
	controlPanel->hideLoading();
	playerWindow->setWindowTitle("");
	thisOptions->stopPlaying();
	thisOptionsLoad->stopPlaying();
}
void IndigoPlayer::clickRewind() {
	filePlayer->rewindPlayFile();
}
void IndigoPlayer::clickMute() {
	filePlayer->setVolume(0);
}
void IndigoPlayer::clickSound() {
	filePlayer->setVolume(controlPanel->getAudioLevel());
}
void IndigoPlayer::changeTimeLine() {
	filePlayer->seekTime(controlPanel->getTime());
}
void IndigoPlayer::changeSoundLevel() {
	filePlayer->setVolume(controlPanel->getAudioLevel());
}
void IndigoPlayer::quit() {
	stopPlayer();
	Gtk::Main::quit();
}
IndigoPlayer::~IndigoPlayer() {
	delete generator;
}
