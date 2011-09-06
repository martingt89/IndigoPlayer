/*
 * ColorSetings.cpp
 *
 *  Created on: 2.9.2011
 *      Author: xgeier
 */

#include "ColorSetings.h"

ColorSetings::ColorSetings(MplayerInterface* mplayer, SavedFileInfo* info) {
	this->mplayer = mplayer;
	this->info = info;
}
void ColorSetings::setHue(double hue){
	mplayer->setHue(hue);
	info->setHue(hue);
}
void ColorSetings::setGamma(double gama){
	mplayer->setGamma(gama);
	info->setGamma(gama);
}
void ColorSetings::setContrast(double con){
	mplayer->setContrast(con);
	info->setContrast(con);
}
void ColorSetings::setSaturation(double satur){
	mplayer->setSaturation(satur);
	info->setSaturation(satur);
}
void ColorSetings::setBrightness(double bright){
	mplayer->setBrightness(bright);
	info->setBrightness(bright);
}
