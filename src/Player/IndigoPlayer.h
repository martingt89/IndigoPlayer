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
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "Playlist.h"

#include <list>
#include <glibmm/ustring.h>

class IndigoPlayer: public PlayerSignals {
public:
	IndigoPlayer(BasePlayerWindow *bsw);
	virtual ~IndigoPlayer();
	void setPlaylist(Playlist *playlist);
	void setVideoBoard(VideoBoard* board);
	void setOpenDialog(OpenFileDialog* dialog);
	void clickPlay();
	void clickPause();
	void clickForward();
	void clickBackward();
	void clickCancel();
	void clickFullscreen();
	void clickThisOptions();
	void clickPlaylistBoard();
	void clickKill();
	void clickOpen();
	void clickRewind();
	void clickMute();
	void clickSound();
	void changeTimeLine();
	void changeSoundLevel();
	void addFiles(std::list<IndigoFile*> files, bool play);
	void playFile(IndigoFile* file);
	void stopPlayer();
private:
	BasePlayerWindow *basePlayerWindow;
	Playlist* playlist;
	VideoBoard* videoBoard;
	OpenFileDialog* openDialog;
};

#endif /* PLAYER_H_ */
