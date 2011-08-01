/*
 * Player.h
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Interfaces/PlayerSignals.h"
#include "../Graphic/BasePlayerWindow.h"

class Player: public PlayerSignals {
public:
	Player(BasePlayerWindow *bsw);
	virtual ~Player();
	void clickPlay();
	void clickStop();
	void clickForward();
	void clickBackward();
	void clickCancel();
	void clickFullscreen();
	void clickThisOptions();
	void clickPlaylist();
	void clickKill();
	void clickOpen();
	void clickRewind();
	void clickMute();
	void clickSound();
	void changeTimeLine();
	void changeSoundLevel();
private:
	BasePlayerWindow *basePlayerWindow;
};

#endif /* PLAYER_H_ */
