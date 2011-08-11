/*
 * Player.h
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Interfaces/PlayerSignals.h"
#include "../Graphic/ControlPanel.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "../Graphic/PlayerWindow.h"
#include "../PlayerKernel/PlayerKernel.h"
#include "../PlayerKernel/ScriptGenerator.h"
#include "Playlist.h"

#include <list>
#include <glibmm/ustring.h>
#include <gtkmm/main.h>

class IndigoPlayer: public PlayerSignals {
public:
	IndigoPlayer(PlayerWindow *playerWin);
	virtual ~IndigoPlayer();
	void setPlaylist(Playlist *playlist);
	void setVideoBoard(VideoBoard* board);
	void setOpenDialog(OpenFileDialog* dialog);
	void setControlPanel(ControlPanel* control);
	void messageIncomming();
	void clickPlay();
	void clickPause();
	void clickForward();
	void clickBackward();
	void clickCancel();
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
	void quit();
private:
	PlayerWindow *playerWindow;
	Playlist* playlist;
	VideoBoard* videoBoard;
	OpenFileDialog* openDialog;
	ControlPanel* controlPanel;
	PlayerKernel* kernel;
	ScriptGenerator* generator;
	StringAnalyze* mediaPackage;
};

#endif /* PLAYER_H_ */
