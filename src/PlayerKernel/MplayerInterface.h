/*
 * MplayerInterface.h
 *
 *  Created on: 15.8.2011
 *      Author: xgeier
 */

#ifndef MPLAYERINTERFACE_H_
#define MPLAYERINTERFACE_H_

#include "MediaPackage.h"
#include "PlayerKernel.h"
#include "ScriptGenerator.h"
#include "../Files/IndigoFile.h"

class MplayerInterface {
public:
	MplayerInterface(MediaPackage* media);
	virtual ~MplayerInterface();
	void setGenerator(ScriptGenerator* gener);
	bool play(IndigoFile* file, bool loadTime=false, SavedFileInfo* info=NULL);
	bool isPlaying();
	void mute(bool mut);
	void soundLevel(double level);
	void changeTime(int time);
	void pause();
	void resume();
	void stopPlayback();
	void setContrast(double con);
	void setGamma(double gama);
	void setHue(double hue);
	void setSaturation(double satur);
	void setBrightness(double bright);
	void setPlaySpeed(double speed);
	void playAudio(int number);
	void playAudioPath(Glib::ustring path);
	void playSubtitles(int number, bool orig);
	void loadSubtitles(Glib::ustring file);
	void relativeSeek(int time);
	void setSubtitleDelay(double delay, bool paint);
private:
	MediaPackage* mediaPackage;
	PlayerKernel* kernel;
	bool isPlayNoPause;
};

#endif /* MPLAYERINTERFACE_H_ */
