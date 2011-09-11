/*
 * GraphicLoader.h
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 */

#ifndef GRAPHICLOADER_H_
#define GRAPHICLOADER_H_

#include <iostream>
#include <gtkmm/builder.h>
#include "../Graphic/ControlPanel.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "../Graphic/PlaylistGraphic.h"
#include "../GraphicLogic/Playlist.h"
#include "../Graphic/PlayerWindow.h"
#include "../Graphic/ThisOptions.h"
#include "../Graphic/ThisOptionsLoad.h"
#include "../Settings.h"

class GraphicLoader {
public:
	GraphicLoader();
	virtual ~GraphicLoader();
	PlayerWindow *getPlayerWindow();
	ControlPanel* getBasePlayerWindow();
	VideoBoard* getVideoBoard();
	OpenFileDialog* getOpenDialog();
	Playlist* getPlaylist();
	ThisOptions *getThisOptions();
	ThisOptionsLoad *getThisOptionsLoad();
private:
	PlayerWindow *playerWindow;
	ControlPanel *controlPanel;
	OpenFileDialog* openWindow;
	VideoBoard *videoBoard;
	ThisOptions* thisOptions;
	ThisOptionsLoad* thisOptionsLoad;
	Playlist* playlistLogic;
};

#endif /* GRAPHICLOADER_H_ */
