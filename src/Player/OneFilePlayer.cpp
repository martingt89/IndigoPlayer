/*
 * OneFilePlayer.cpp
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#include "OneFilePlayer.h"
#include <iostream>
OneFilePlayer::OneFilePlayer() {
	mediaPackage = new MediaPackage();
	mplayer = new MplayerInterface(mediaPackage);
	colors = new ColorSetings(mplayer);
	mediaPackage->message.connect(sigc::mem_fun(this, &OneFilePlayer::incommingMessage));
	playerSignal = NULL;
	firstStart = true;
	endCounter = 0;
	startingLoading = false;
	startloadedSubtitle = "";
	initHashTable(hashTableOfFunction);
}

OneFilePlayer::~OneFilePlayer() {
	delete mediaPackage;
	delete mplayer;
}
void OneFilePlayer::setGenerator(ScriptGenerator* generator){
	mplayer->setGenerator(generator);
}
void OneFilePlayer::setGraphicPointer(PlayerSignals* signal){
	playerSignal = signal;
}
ColorSetings* OneFilePlayer::getColorSettings(){
	return colors;
}
//-----------------ANALYZE----------------------------//
void OneFilePlayer::incommingMessage(){
	bool sendPackage = false;
	GraphicData dat;
//	if(mediaPackage->isStart(false)){
//		std::cerr<<"DEBUG: mediaPackage->isStart() = false firstStart = "<<firstStart<<std::endl;
//	}
	if (firstStart && mediaPackage->isStart(true)){
		firstStart = false;
		sendPackage = true;
		dat.setStart(true);
	}
	if (mediaPackage->isEnd(true)){
		if(endCounter == 0){
			sendPackage = true;
			dat.setEnd(true);
		}else{
			endCounter--;
		}
	}
	if (mediaPackage->getVariable("ANS_TIME_POSITION").size() != 0) {
		int aktual = mediaPackage->getVariableAsInteger("ANS_TIME_POSITION");
		info.setAktulaTime(aktual);
		dat.setAktualTime(aktual);
		sendPackage = true;
	}

	if (mediaPackage->isVideoParamChange()) {
		if (mediaPackage->getVariable("ID_LENGTH").size() != 0) {
			dat.setLength(mediaPackage->getVariableAsInteger("ID_LENGTH"));
			sendPackage = true;
		}
		int h = mediaPackage->getVariableAsInteger("ID_VIDEO_HEIGHT");
		int w = mediaPackage->getVariableAsInteger("ID_VIDEO_WIDTH");
		if (h > 0 && w > 0){
			dat.setResolution(w,h);
			info.setResolution(w, h);
			sendPackage = true;
		}
	}

	if(startingLoading){
		int sub = mediaPackage->getValueFromSubtitlePath(startloadedSubtitle);
		if(sub != -1){
			startingLoading = false;
			mplayer->playSubtitles(sub);
			info.setSubtitlePath(startloadedSubtitle);
		}
	}
	if (mediaPackage->isSubtitleChanged()) {
		dat.setSubtitleList(mediaPackage->getListSubtitles());
	}
	if (mediaPackage->isAudioChanged()) {
		dat.setAudioList(mediaPackage->getListAudios());
	}

	if(sendPackage && playerSignal)
		playerSignal->incommingMessage(dat);
}
//-----------------ANALYZE----------------------------//
void OneFilePlayer::playFile(IndigoFile* file){
	stopPlayFile();
	if(file == NULL) return;
	endCounter = 0;
	startloadedSubtitle = "";
	startingLoading = false;
	aktualFile = *file;
	info.clear();
	info.setSoundPosition(file->getSoundDelayms()/1000.0);
	info.setSubtitlePosition(file->getSubtitleDelayms()/1000.0);
	if(!mplayer->play(&aktualFile)){
		mediaPackage->analyze("ID_EXIT");
	}
	firstStart = true;
}
void OneFilePlayer::reloadPlayback(){
	endCounter++;
	stopPlayFile();
	mplayer->play(&aktualFile, true, &info);
}
void OneFilePlayer::rewindPlayFile(){
	endCounter++;
	stopPlayFile();
	mplayer->play(&aktualFile, false, &info);
}
void OneFilePlayer::pausePlayFile(){
	mplayer->pause();
}
void OneFilePlayer::stopPlayFile(){
	mplayer->stopPlayback();
	mediaPackage->clear();
}
void OneFilePlayer::playSubtitles(Glib::ustring subtitles){
	int sub = mediaPackage->getValueFromSubtitlePath(subtitles);
	if(sub == -1) { 						//subtitle is not loaded
		mplayer->loadSubtitles(subtitles);
		startloadedSubtitle = subtitles;
		startingLoading = true;
	}else{
		mplayer->playSubtitles(sub);
		if(mediaPackage->isOriginalSubtitleStream(sub))
			info.setSubtitleID(sub);
		else
			info.setSubtitlePath(subtitles);
	}
}
void OneFilePlayer::hideSubtitles(){
	mplayer->playSubtitles(-1);
	info.setSubtitleID(-1);
}
void OneFilePlayer::playSound(Glib::ustring sound){
	int sau = mediaPackage->getValueFromAudioText(sound);
	if(sau == -1){
		info.setAudioPath(sound);
		reloadPlayback();
	}else{
		info.setAudioID(sau);
		mplayer->playAudio(sau);
	}
}
//:::::::::::::::::::::::::::::::::::::::::::::::
void OneFilePlayer::setRotateFilter(int degrees, bool apply){
	info.setRotate(degrees);
	if(apply)
		reloadPlayback();
}
void OneFilePlayer::cropFilter(int top, int right, int botton, int left, bool apply){
	info.setCrop(top, botton, left, right);
	if(apply)
		reloadPlayback();
}
void OneFilePlayer::setVolume(int volume){
	mplayer->soundLevel(volume);
}
void OneFilePlayer::setPlaySpeed(double speed){
	info.setPlaySpeed(speed);
	mplayer->setPlaySpeed(speed);
}
void OneFilePlayer::apply(){
	reloadPlayback();
}
//:::::::::::::::::::::::::::::::::::::::::::::::
void OneFilePlayer::subtitleMoveForward(){
	double pos = info.getSubtitlePosition();
	pos += 0.1;
	info.setSubtitlePosition(pos);
}
void OneFilePlayer::subtitleMoveBackward(){
	double pos = info.getSubtitlePosition();
	pos -= 0.1;
	info.setSubtitlePosition(pos);
}
void OneFilePlayer::timeMoveForward(){
	double pos = info.getSoundPosition();
	pos += 0.1;
	info.setSoundPosition(pos);
}
void OneFilePlayer::timeMoveBackward(){
	double pos = info.getSoundPosition();
	pos -= 0.1;
	info.setSoundPosition(pos);
}
void OneFilePlayer::seekTime(int time){
	mplayer->changeTime(time);
}
//:::::::::::::::::::::::::::::::::::::::::::::::
void OneFilePlayer::timeShorJumpForward(){
	mplayer->relativeSeek(10);
}
void OneFilePlayer::timeShorJumpBackward(){
	mplayer->relativeSeek(-10);
}
void OneFilePlayer::timeLongJumpForward(){
	mplayer->relativeSeek(100);
}
void OneFilePlayer::timeLongJumpBackward(){
	mplayer->relativeSeek(-100);
}
//::::::::::::::::::::::::::::::::::::::::::::::::
void OneFilePlayer::initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table){
	table[IndigoPlayerEnum::SHORFORWARD] = &OneFilePlayer::timeShorJumpForward;
	table[IndigoPlayerEnum::SHORBACKWARD] = &OneFilePlayer::timeShorJumpBackward;
	table[IndigoPlayerEnum::LONGFORWARD] = &OneFilePlayer::timeLongJumpForward;
	table[IndigoPlayerEnum::LONGBACKWARD] = &OneFilePlayer::timeLongJumpBackward;
}
void OneFilePlayer::call(IndigoPlayerEnum::Command command){
	if(hashTableOfFunction.find(command) != hashTableOfFunction.end()){
		OFP func = hashTableOfFunction[command];
		(this->*func)();
	}
}
std::list<IndigoPlayerEnum::Command> OneFilePlayer::getCommandList(){
	std::list<IndigoPlayerEnum::Command> list;
	std::map <IndigoPlayerEnum::Command, OFP>::iterator it;
	for(it = hashTableOfFunction.begin(); it != hashTableOfFunction.end(); it++){
		list.push_back(it->first);
	}
	return list;
}
