/*
 * ColorSetings.h
 *
 *  Created on: 2.9.2011
 *      Author: xgeier
 */

#ifndef COLORSETINGS_H_
#define COLORSETINGS_H_

#include "../PlayerKernel/MplayerInterface.h"

class ColorSetings {
public:
	ColorSetings(MplayerInterface* mplayer, SavedFileInfo* info);
	//=========================
	void setHue(double hue);
	void setGamma(double gama);
	void setContrast(double con);
	void setSaturation(double satur);
	void setBrightness(double bright);
private:
	MplayerInterface* mplayer;
	SavedFileInfo* info;
};

#endif /* COLORSETINGS_H_ */
