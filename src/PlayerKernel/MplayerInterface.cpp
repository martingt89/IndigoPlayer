/*
 * MplayerInterface.cpp
 *
 *  Created on: 15.8.2011
 *      Author: xgeier
 */

#include "MplayerInterface.h"

MplayerInterface::MplayerInterface(StringAnalyze* media) {
	mediaPackage = media;
	kernel = new PlayerKernel(mediaPackage);
	filter = new VideoFilters();
	isPlayNoPause = true;
}

MplayerInterface::~MplayerInterface() {
	delete kernel;
	delete filter;
}

void MplayerInterface::setGenerator(ScriptGenerator* gener) {
	gener->setVideoFilters(filter);
	kernel->setGenerator(gener);
}

bool MplayerInterface::play(IndigoFile* file) {
	isPlayNoPause = true;
	return kernel->play(file);
}
void MplayerInterface::applyFilters() {
	if (kernel->isPlaying())
		kernel->rebootPlay();
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
}
void MplayerInterface::changeTime(int time) {
	kernel->sendCommand("seek " + Glib::ustring::format(time) + " 2\n");
}
void MplayerInterface::pause() {
	if (isPlayNoPause == true) {
		kernel->sendCommand("pause\n osd_show_text pause\n");
	}
	isPlayNoPause = false;
}
void MplayerInterface::resume() {
	if (isPlayNoPause == false) {
		kernel->sendCommand("pause\n osd_show_text unpause\n");
	}
	isPlayNoPause = true;
}
void MplayerInterface::cancel() {
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
void MplayerInterface::crop(int a, int b, int c, int d) {
	filter->resize(a, b, c, d);
}
void MplayerInterface::rotate(int deg){
	filter->rotate(deg);
}
