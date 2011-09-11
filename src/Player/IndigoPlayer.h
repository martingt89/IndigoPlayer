/*
 * Player.h
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "OneFilePlayer.h"
#include "GraphicData.h"
#include "../ConfigFile.h"
#include "../Interfaces/PlayerSignals.h"
#include "../Interfaces/Callable.h"
#include "../Graphic/ControlPanel.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "../Graphic/PlayerWindow.h"
#include "../Graphic/ThisOptions.h"
#include "../Graphic/ThisOptionsLoad.h"
#include "../GraphicLogic/Playlist.h"
#include "../PlayerKernel/MplayerInterface.h"
#include "../PlayerKernel/ScriptGenerator.h"

#include <map>
#include <list>
#include <gtkmm/main.h>
#include <glibmm/ustring.h>

class IndigoPlayer: public PlayerSignals {
public:
	IndigoPlayer(PlayerWindow *playerWin, OneFilePlayer* player);
	virtual ~IndigoPlayer();
	void setPlaylist(Playlist *playlist);
	void setVideoBoard(VideoBoard* board);
	void setOpenDialog(OpenFileDialog* dialog);
	void setControlPanel(ControlPanel* control);
	void setThisOptions(ThisOptions* opt);
	void setThisOptionsLoad(ThisOptionsLoad* optLoad);
//-------------------------------------------------------------------------
	void playNextFile();
	void clickForwardSoftware();
	void addSubtitle(Glib::ustring file);
	void clickPlay();
	void clickPause();
	void clickForward();
	void clickBackward();
	void clickCancel();
	void clickPlaylistBoard();
	void clickRewind();
	void clickMute();
	void clickSound();
	void changeTimeLine();
	void changeSoundLevel();
	void addFiles(std::list<IndigoFile*> files, bool play);
	void playFile(IndigoFile* file);
	void incommingMessage(GraphicData data);
	void stopPlayer();
	void quit();
private:
	void clearPlaying();
	void playSubtitles(Glib::ustring sub);
	void playAudio(Glib::ustring name);
	PlayerWindow *playerWindow;
	Playlist* playlist;
	VideoBoard* videoBoard;
	OpenFileDialog* openDialog;
	ControlPanel* controlPanel;
	ThisOptions* thisOptions;
	ThisOptionsLoad* thisOptionsLoad;
	ScriptGenerator* generator;
	OneFilePlayer* filePlayer;
	ConfigFile config;

	IndigoFile* nextFile;
	bool stopPlay;
	bool playing;
};

#endif /* PLAYER_H_ */
