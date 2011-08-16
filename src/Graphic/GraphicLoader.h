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
#include "../../Settings.h"
#include "ControlPanel.h"
#include "VideoBoard.h"
#include "OpenFileDialog.h"
#include "PlaylistGraphic.h"
#include "PlayerWindow.h"
#include "ThisOptions.h"

class GraphicLoader {
public:
	GraphicLoader();
	virtual ~GraphicLoader();
	PlayerWindow *getPlayerWindow();
	ControlPanel* getBasePlayerWindow();
	VideoBoard* getVideoBoard();
	OpenFileDialog* getOpenDialog();
	PlaylistGraphic* getPlaylistGraphic();
	ThisOptions *getThisOptions();
private:
	PlayerWindow *playerWindow;
	ControlPanel *controlPanel;
	OpenFileDialog* openWindow;
	VideoBoard *videoBoard;
	PlaylistGraphic* playlist;
	ThisOptions* thisOptions;
};

#endif /* GRAPHICLOADER_H_ */
