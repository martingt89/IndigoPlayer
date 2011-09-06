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
	colors = new ColorSetings(mplayer, &info);
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
	bool start = false;
	bool fs = false;
	GraphicData dat;
	if(mediaPackage->isStart(false)){
		start = true;
		sendPackage = true;
		fs = firstStart;
	}
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
		int sub = mediaPackage->getSubtitleNumberFromName(startloadedSubtitle);
		if(sub != -1){
			startingLoading = false;
			info.setSubtitlePosition(0);
			mplayer->playSubtitles(sub, false);
			info.setSubtitlePath(startloadedSubtitle);
		}
	}
	if (mediaPackage->isSubtitleChanged()) {
		dat.setSubtitleList(mediaPackage->getListSubtitles());
		sendPackage = true;
	}
	if (mediaPackage->isAudioChanged()) {
		dat.setAudioList(mediaPackage->getListAudios());
		sendPackage = true;
	}
	if(start){
		start = false;
		this->loadVideoSpecialThings(dat, fs);
	}
	if(sendPackage && playerSignal)
		playerSignal->incommingMessage(dat);
}
//-----------------ANALYZE----------------------------//
void OneFilePlayer::loadVideoSpecialThings(GraphicData &dat, bool firstStart){
	if(info.getPause()){
		mplayer->pause();
	}
	//load audio
	if(info.getAudioID() != -1){
		mplayer->playAudio(info.getAudioID());
		Glib::ustring tt = mediaPackage->getAudioNameFromNumber(info.getAudioID());
		if(tt.size() > 0)
			dat.setAktualAudio(tt);
	}else if(info.getAudioPath().size() == 0){
		std::list<Glib::ustring> aud = mediaPackage->getListAudios();
		if(aud.size()!= 0){
			mplayer->playAudio(mediaPackage->getAudioNumberFromName(*(aud.begin())));
			dat.setAktualAudio(*(aud.begin()));
		}
	} else if (info.getAudioPath().size() != 0){
		dat.setAktualAudio(info.getAudioPath());
	}
	//loadAudio
	//loadSubtitle
	if(info.getSubID() != -1){
		mplayer->playSubtitles(info.getSubID(), true);
		Glib::ustring tt = mediaPackage->getSubtitleNameFromNumber(info.getSubID(), true);
		if(tt.size() > 0){
			dat.setAktualSubtitle(tt);
		}
	}else if(info.getSubPath().size() == 0 && firstStart){
		std::list<Glib::ustring> sub = mediaPackage->getListSubtitles();
		if(sub.size() != 0){
			std::list<Glib::ustring>::iterator it;
			for(it = sub.begin(); it != sub.end(); it++){
				if(!mediaPackage->isOriginalSubtitleFromName(*it)){
					mplayer->playSubtitles(mediaPackage->getSubtitleNumberFromName(*it), false);
					dat.setAktualSubtitle(*it);
					break;
				}
			}
		}
	} else if(info.getSubPath().size() != 0){
		dat.setAktualSubtitle(info.getSubPath());
	}
	//loadSubtitles
}
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
	info.pause();
}
void OneFilePlayer::stopPlayFile(){
	mplayer->stopPlayback();
	mediaPackage->clear();
}
void OneFilePlayer::playSubtitles(Glib::ustring subtitles){
	int sub = mediaPackage->getSubtitleNumberFromName(subtitles);
	if(sub == -1) { 						//subtitle is not loaded
		mplayer->loadSubtitles(subtitles);
		startloadedSubtitle = subtitles;
		startingLoading = true;
	}else{
		if(mediaPackage->isOriginalSubtitleFromName(subtitles)){
			info.setSubtitleID(sub);
			info.setSubtitlePosition(0);
			mplayer->playSubtitles(sub, true);
		}else{
			info.setSubtitlePath(subtitles);
			info.setSubtitlePosition(0);
			mplayer->playSubtitles(sub, false);
		}
	}
}
void OneFilePlayer::hideSubtitles(){
	mplayer->playSubtitles(-1, true);
	info.setSubtitleID(-1);
}
void OneFilePlayer::playSound(Glib::ustring sound){
	int sau = mediaPackage->getAudioNumberFromName(sound);
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
	mplayer->setSubtitleDelay(pos, true);
}
void OneFilePlayer::subtitleMoveBackward(){
	double pos = info.getSubtitlePosition();
	pos -= 0.1;
	info.setSubtitlePosition(pos);
	mplayer->setSubtitleDelay(pos, true);
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
	table[IndigoPlayerEnum::SUBFORWARD] = &OneFilePlayer::subtitleMoveForward;
	table[IndigoPlayerEnum::SUBBACKWARD] = &OneFilePlayer::subtitleMoveBackward;
	table[IndigoPlayerEnum::AUDFORWARD] = &OneFilePlayer::timeMoveForward;
	table[IndigoPlayerEnum::AUDBACKWARD] = &OneFilePlayer::timeMoveBackward;
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
