/*
 * ColorSetings.cpp
 *
 *  Created on: 2.9.2011
 *      Author: xgeier
 */

#include "ColorSetings.h"

ColorSetings::ColorSetings(MplayerInterface* mplayer) {
	this->mplayer = mplayer;
}
void ColorSetings::setHue(double hue){
	mplayer->setHue(hue);
}
void ColorSetings::setGamma(double gama){
	mplayer->setGamma(gama);
}
void ColorSetings::setContrast(double con){
	mplayer->setContrast(con);
}
void ColorSetings::setSaturation(double satur){
	mplayer->setSaturation(satur);
}
void ColorSetings::setBrightness(double bright){
	mplayer->setBrightness(bright);
}
