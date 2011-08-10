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
}
void IndigoPlayer::setPlaylist(Playlist *playlist) {
	this->playlist = playlist;
	this->playlist->setListener(this);
}
void IndigoPlayer::setVideoBoard(VideoBoard* board) {
	this->videoBoard = board;
}
void IndigoPlayer::setControlPanel(ControlPanel* control){
	controlPanel = control;
	controlPanel->setListener(this);
}
void IndigoPlayer::setOpenDialog(OpenFileDialog* dialog) {
	openDialog = dialog;
	openDialog->setListener(this);
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
	playlist->aktualizeFile();
	this->playFile(playlist->getFile());
}
void IndigoPlayer::stopPlayer() {

}
void IndigoPlayer::playFile(IndigoFile* file) {

}
void IndigoPlayer::clickPlay() {
	if (playlist->isEmpty()) {
		openDialog->show();
		controlPanel->popPlayButton();
		return;
	}
	this->stopPlayer();
	this->playFile(playlist->getFile());
}
void IndigoPlayer::clickPause() {

}
void IndigoPlayer::clickForward() {
	if(true){
		this->stopPlayer();
		playlist->goNextFile();
		this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickBackward() {
	if(true){
		this->stopPlayer();
		playlist->goPrevioseFile();
		this->playFile(playlist->getFile());
	}
}
void IndigoPlayer::clickCancel() {
	this->stopPlayer();
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

}
void IndigoPlayer::clickSound() {

}
void IndigoPlayer::changeTimeLine() {

}
void IndigoPlayer::changeSoundLevel() {

}
IndigoPlayer::~IndigoPlayer() {
	//tu asi nic nebude, nic nevytvaram na hromade
}
