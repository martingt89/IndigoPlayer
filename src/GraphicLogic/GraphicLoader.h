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
#include "GraphicPathLoader.h"
#include "../Files/Logger.h"
#include "../Graphic/ControlPanel.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "../Graphic/Options.h"
#include "../Graphic/PlaylistGraphic.h"
#include "../Graphic/PlayerWindow.h"
#include "../Graphic/ThisOptions.h"
#include "../Graphic/ThisOptionsLoad.h"
#include "../GraphicLogic/Playlist.h"
#include "../Settings.h"

class GraphicLoader {
public:
	GraphicLoader() throw (int);
	virtual ~GraphicLoader();
	PlayerWindow *getPlayerWindow();
	ControlPanel* getBasePlayerWindow();
	VideoBoard* getVideoBoard();
	OpenFileDialog* getOpenDialog();
	Options* getOptionsWindow();
	Playlist* getPlaylist();
	ThisOptions *getThisOptions();
	ThisOptionsLoad *getThisOptionsLoad();
private:
	PlayerWindow *playerWindow;
	ControlPanel *controlPanel;
	OpenFileDialog* openWindow;
	Options* optionsWindow;
	VideoBoard *videoBoard;
	ThisOptions* thisOptions;
	ThisOptionsLoad* thisOptionsLoad;
	Playlist* playlistLogic;

	GraphicPathLoader pathLoader;
	IndigoLogger::Logger log;
};

#endif /* GRAPHICLOADER_H_ */
