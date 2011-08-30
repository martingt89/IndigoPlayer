/*
 * Player.h
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Interfaces/PlayerSignals.h"
#include "../Interfaces/Callable.h"
#include "../Graphic/ControlPanel.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "../Graphic/PlayerWindow.h"
#include "../Graphic/ThisOptions.h"
#include "../Graphic/ThisOptionsLoad.h"
#include "../PlayerKernel/MplayerInterface.h"
#include "../PlayerKernel/ScriptGenerator.h"

#include "Playlist.h"
#include "ShortKeys.h"

#include <list>
#include <map>
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
	void setThisOptions(ThisOptions* opt);
	void setThisOptionsLoad(ThisOptionsLoad* optLoad);
	void messageIncomming();
	void addSubtitle(Glib::ustring file);
	void keyPressed(int control, int keyVal, unsigned short hardwareKey);
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
	void clearPlaying();
	void playSubtitles(Glib::ustring sub);
	void playAudio(Glib::ustring name);
	PlayerWindow *playerWindow;
	Playlist* playlist;
	VideoBoard* videoBoard;
	OpenFileDialog* openDialog;
	ControlPanel* controlPanel;
	MplayerInterface* mplayer;
	ScriptGenerator* generator;
	MediaPackage* mediaPackage;
	ThisOptions* thisOptions;
	ThisOptionsLoad* thisOptionsLoad;
	bool playSub;
	bool firstLogSub;
	bool firstLogAud;
	Glib::ustring subtitles;
	ShortKeys shortKeys;
};

#endif /* PLAYER_H_ */
