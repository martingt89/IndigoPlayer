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
	isPlayNoPause = true;
}

MplayerInterface::~MplayerInterface() {
	delete kernel;
}

void MplayerInterface::setGenerator(ScriptGenerator* gener) {
	kernel->setGenerator(gener);
}

bool MplayerInterface::play(IndigoFile* file, bool loadTime, SavedFileInfo* info) {
	isPlayNoPause = true;
	return kernel->play(file, loadTime, info);
}
void MplayerInterface::loadSubtitles(Glib::ustring file){
	kernel->sendCommand("sub_load '"+file+"'\n");
}
void MplayerInterface::playSubtitles(int number, bool orig){
	if(orig)
		kernel->sendCommand("sub_demux "+Glib::ustring::format(number)+"\n");
	else
		kernel->sendCommand("sub_file "+Glib::ustring::format(number)+"\n");
}
void MplayerInterface::playAudio(int number){
	kernel->sendCommand("switch_audio "+Glib::ustring::format(number)+"\n");
}
void MplayerInterface::relativeSeek(double time){
	kernel->sendCommand("seek " + Glib::ustring::format(time) + " 0\n");
}
void MplayerInterface::setSubtitleDelay(double delay, bool paint){
	if(delay < 0.1 && delay > -0.1)
		delay = 0;
	kernel->sendCommand("sub_delay "+Glib::ustring::format(delay)+" 1 \n");
	if(paint)
		kernel->sendCommand("osd_show_text 'subtitle delay "+Glib::ustring::format(delay*1000)+" ms' \n");
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
	kernel->pausePlayer();
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
