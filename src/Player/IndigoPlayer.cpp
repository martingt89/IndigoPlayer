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
	mediaPackage = new MediaPackage();
	mplayer = new MplayerInterface(mediaPackage);
	generator = new ScriptGenerator();
	mediaPackage->message.connect(sigc::mem_fun(this, &IndigoPlayer::messageIncomming));
	playSub = false;
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
void IndigoPlayer::setThisOptions(ThisOptions* opt){
	thisOptions = opt;
	thisOptions->setPlayerInt(mplayer);
}
void IndigoPlayer::messageIncomming(){
	if(mediaPackage->isVideoParamChange()){
		if(mediaPackage->getVariable("ID_LENGTH").size() != 0){
			controlPanel->setDuration(mediaPackage->getVariableAsInteger("ID_LENGTH"));
		}
		int h = mediaPackage->getVariableAsInteger("ID_VIDEO_HEIGHT");
		int w = mediaPackage->getVariableAsInteger("ID_VIDEO_WIDTH");
		if(h > 0 && w > 0)
			videoBoard->setVideoResolution(w, h, true);
	}
	if(mediaPackage->getVariable("ANS_TIME_POSITION").size() != 0){
		controlPanel->setPosition(mediaPackage->getVariableAsInteger("ANS_TIME_POSITION"));
	}
	if(mediaPackage->getVariable("EXIT").size() != 0){
		clearPlaying();
		clickForward();
	}
	if(playSub){
		int ret = mediaPackage->getValueFromSubtitlePath(subtitles);
		if(ret != -1){
			std::cout<<"SPUSTAM: "<<ret<<std::endl;
			playSub = false;
			mplayer->playSubtitles(ret);
		}
	}
}
void IndigoPlayer::addSubtitle(Glib::ustring file){
	if(mplayer->isPlaying()){
		thisOptions->addSubtitles(file, true);
		playSubtitles(file);
	}
}
void IndigoPlayer::playSubtitles(Glib::ustring sub){
	mplayer->loadSubtitles(sub);
	subtitles = sub;
	playSub = true;
}
void IndigoPlayer::keyPressed(int control, int keyVal){
//	std::cout<<control<<" "<<keyVal<<std::endl;
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
	mplayer->cancel();
	this->clearPlaying();
}
void IndigoPlayer::playFile(IndigoFile* file) {
	if(file != NULL){
		mplayer->setGenerator(generator);
		videoBoard->showLogo(false);
		if(mplayer->play(file)){
			controlPanel->pushPlayButton();
			playerWindow->setWindowTitle(file->getName());
		}else{
			//asi nejake logy
		}
	}
}
void IndigoPlayer::clickPlay() {
	if(!mplayer->isPlaying()){
		if (playlist->isEmpty()) {
			openDialog->show();
			controlPanel->popPlayButton();
			return;
		}
		this->stopPlayer();
		IndigoFile* file = playlist->getFile();
		if(file == NULL){
			openDialog->show();
			controlPanel->popPlayButton();
		}else{
			this->playFile(file);
		}
	}else{
		mplayer->resume();
	}
}
void IndigoPlayer::clickPause() {
	mplayer->pause();
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
	if(thisOptions)
		thisOptions->show();
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
	mplayer->mute(true);
}
void IndigoPlayer::clickSound() {
	mplayer->soundLevel(controlPanel->getAudioLevel());
	mplayer->mute(false);
}
void IndigoPlayer::changeTimeLine() {
	mplayer->changeTime(controlPanel->getTime());
}
void IndigoPlayer::changeSoundLevel() {
	mplayer->soundLevel(controlPanel->getAudioLevel());
}
void IndigoPlayer::quit(){
	mplayer->cancel();
	Gtk::Main::quit();
}
IndigoPlayer::~IndigoPlayer() {
	delete mediaPackage;
	delete mplayer;
	delete generator;
}
