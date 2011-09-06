/*
 * OneFilePlayer.h
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#ifndef ONEFILEPLAYER_H_
#define ONEFILEPLAYER_H_

#include <glibmm/ustring.h>
#include "ColorSetings.h"
#include "SavedFileInfo.h"
#include "../Files/IndigoFile.h"
#include "../PlayerKernel/MplayerInterface.h"
#include "../PlayerKernel/ScriptGenerator.h"
#include "../Interfaces/VideoFilters.h"
#include "../Interfaces/Callable.h"

class OneFilePlayer : public VideoFilters, public Callable {
public:
	OneFilePlayer();
	virtual ~OneFilePlayer();
	void setGenerator(ScriptGenerator* generator);
	void setGraphicPointer(PlayerSignals* signal);
	ColorSetings* getColorSettings();
	void incommingMessage();
	//========================
	void playFile(IndigoFile* file);
	void reloadPlayback();
	void rewindPlayFile();
	void pausePlayFile();
	void stopPlayFile();
	void playSubtitles(Glib::ustring subtitles);
	void hideSubtitles();
	void playSound(Glib::ustring sound);
	//========================
	void setRotateFilter(int degrees, bool apply=false);
	void cropFilter(int top, int right, int botton, int left, bool apply=false);
	void setVolume(int volume);
	void setPlaySpeed(double speed);
	void apply();
	//========================
	void subtitleMoveForward();
	void subtitleMoveBackward();
	void timeMoveForward();
	void timeMoveBackward();
	void seekTime(int time);
	//========================
	void timeShorJumpForward();
	void timeShorJumpBackward();
	void timeLongJumpForward();
	void timeLongJumpBackward();
	//========================
	void call(IndigoPlayerEnum::Command command);
	std::list<IndigoPlayerEnum::Command> getCommandList();
private:
	void loadVideoSpecialThings(GraphicData &dat, bool firstStart);
    typedef void (OneFilePlayer::*OFP)(void);
    std::map <IndigoPlayerEnum::Command, OFP> hashTableOfFunction;
    void initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table);
	IndigoFile aktualFile;
	SavedFileInfo info;
	MplayerInterface* mplayer;
	MediaPackage* mediaPackage;
	PlayerSignals* playerSignal;
	ColorSetings* colors;
	bool firstStart;
	int endCounter;
	Glib::ustring startloadedSubtitle;
	bool startingLoading;
};

#endif /* ONEFILEPLAYER_H_ */
