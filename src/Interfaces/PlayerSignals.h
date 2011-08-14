/*
 * PlayerSignals.h
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#ifndef PLAYERSIGNALS_H_
#define PLAYERSIGNALS_H_

#include <list>
#include "../Files/IndigoFile.h"

class PlayerSignals {
public:
	PlayerSignals();
	virtual ~PlayerSignals();
	virtual void clickPlay() = 0;
	virtual void clickPause() = 0;
	virtual void clickForward() = 0;
	virtual void clickBackward() = 0;
	virtual void clickPlaylistBoard() = 0;
	virtual void clickCancel() = 0;
	virtual void clickThisOptions() = 0;
	virtual void clickKill() = 0;
	virtual void clickOpen() = 0;
	virtual void clickRewind() = 0;
	virtual void clickMute() = 0;
	virtual void clickSound() = 0;
	virtual void changeTimeLine() = 0;
	virtual void changeSoundLevel() = 0;
	virtual void quit() = 0;
	//
	virtual void addFiles(std::list<IndigoFile*> files,  bool play) = 0;
	virtual void addSubtitle(Glib::ustring file) = 0;

	virtual void keyPressed(int control, int keyVal) = 0;
};

#endif /* PLAYERSIGNALS_H_ */
