/*
 * MplayerInterface.h
 *
 *  Created on: 15.8.2011
 *      Author: xgeier
 */

#ifndef MPLAYERINTERFACE_H_
#define MPLAYERINTERFACE_H_

#include "StringAnalyze.h"
#include "PlayerKernel.h"
#include "ScriptGenerator.h"
#include "../Files/IndigoFile.h"
#include "VideoFilters.h"

class MplayerInterface {
public:
	MplayerInterface(StringAnalyze* media);
	virtual ~MplayerInterface();
	void setGenerator(ScriptGenerator* gener);
	bool play(IndigoFile* file);
	bool isPlaying();
	void mute(bool mut);
	void soundLevel(double level);
	void changeTime(int time);
	void pause();
	void resume();
	void cancel();
	void setContrast(double con);
	void setGamma(double gama);
	void setHue(double hue);
	void setSaturation(double satur);
	void setBrightness(double bright);
	void setPlaySpeed(double speed);
	void applyFilters();
	void crop(int a, int b, int c, int d);
	void rotate(int deg);
private:
	StringAnalyze* mediaPackage;
	PlayerKernel* kernel;
	VideoFilters* filter;
	bool isPlayNoPause;
};

#endif /* MPLAYERINTERFACE_H_ */
