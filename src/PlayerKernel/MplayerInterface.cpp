/*
 * MplayerInterface.cpp
 *
 *  Created on: 15.8.2011
 *      Author: xgeier
 */

#include "MplayerInterface.h"
#include <iostream>
MplayerInterface::MplayerInterface(MediaPackage* media) {
	mediaPackage = media;
	kernel = new PlayerKernel(mediaPackage);
//	filter = new VideoFilters();
	isPlayNoPause = true;
}

MplayerInterface::~MplayerInterface() {
	delete kernel;
//	delete filter;
}

void MplayerInterface::setGenerator(ScriptGenerator* gener) {
//	gener->setVideoFilters(filter);
	kernel->setGenerator(gener);
}

bool MplayerInterface::play(IndigoFile* file, bool loadTime, SavedFileInfo* info) {
	isPlayNoPause = true;
	return kernel->play(file, loadTime, info);
}
void MplayerInterface::loadSubtitles(Glib::ustring file){
	kernel->sendCommand("sub_load '"+file+"'\n");
}
void MplayerInterface::playSubtitles(int number){
	kernel->sendCommand("sub_select "+Glib::ustring::format(number)+"\n");
//	if(mediaPackage->isOriginalSubtitleStream(number)){
//		mediaPackage->setAktualPlaySubtitles(number);
//	}else{
//		mediaPackage->setAktualPlaySubtitles(mediaPackage->getSubtitlePathOfStream(number));
//	}
}
void MplayerInterface::playAudio(int number){
	kernel->sendCommand("switch_audio "+Glib::ustring::format(number)+"\n");
//	mediaPackage->setAktualPlayAudio(number);
}
void MplayerInterface::playAudioPath(Glib::ustring path){
//	mediaPackage->setAktualPlayAudio(path);
//	applyFilters();
}
//void MplayerInterface::applyFilters() {
//	if (kernel->isPlaying())
//		kernel->rebootPlay();
//}
//void MplayerInterface::replayFile() {
//	if (kernel->isPlaying())
//		kernel->replay();
//}
void MplayerInterface::relativeSeek(int time){
	kernel->sendCommand("seek " + Glib::ustring::format(time) + " 0\n");
}
bool MplayerInterface::isPlaying() {
	return kernel->isPlaying();
}
void MplayerInterface::mute(bool mut) {
	if (mut)
		kernel->sendCommand("mute 1\n osd_show_text mute\n");
	else
		kernel->sendCommand("mute 0\n osd_show_text unmute\n");
}
void MplayerInterface::soundLevel(double level) {
		kernel->sendCommand("volume " + Glib::ustring::format(level) + " 1\n");
	if(level == 0)
		kernel->sendCommand("osd_show_text mute\n");
	else
		kernel->sendCommand("osd_show_text 'volume: "+Glib::ustring::format(level)+"%' \n");
}
void MplayerInterface::changeTime(int time) {
	kernel->sendCommand("seek " + Glib::ustring::format(time) + " 2\n");
}
void MplayerInterface::pause() {
		kernel->sendCommand("pause\n");
	if (isPlayNoPause) {
		kernel->sendCommand("osd_show_text pause\n");
		isPlayNoPause =false;
	}else{
		isPlayNoPause =true;
		kernel->sendCommand("osd_show_text unpause\n");
	}
}
void MplayerInterface::resume() {
	kernel->sendCommand("pause\n osd_show_text unpause\n");
}
void MplayerInterface::stopPlayback() {
	kernel->stop();
}
void MplayerInterface::setPlaySpeed(double speed) {
	kernel->sendCommand("speed_set " + Glib::ustring::format(speed) + "\n");
}
void MplayerInterface::setContrast(double con) {
	kernel->sendCommand("contrast" + Glib::ustring::format(con) + " 1\n");
}
void MplayerInterface::setGamma(double gama) {
	kernel->sendCommand("gamma " + Glib::ustring::format(gama) + " 1\n");
}
void MplayerInterface::setHue(double hue) {
	kernel->sendCommand("hue " + Glib::ustring::format(hue) + " 1\n");
}
void MplayerInterface::setSaturation(double satur) {
	kernel->sendCommand("saturation " + Glib::ustring::format(satur) + " 1\n");
}
void MplayerInterface::setBrightness(double bright) {
	kernel->sendCommand("brightness " + Glib::ustring::format(bright) + " 1\n");
}
//void MplayerInterface::crop(int a, int b, int c, int d) {
//	filter->resize(a, b, c, d);
//}
//void MplayerInterface::rotate(int deg){
//	filter->rotate(deg);
//}