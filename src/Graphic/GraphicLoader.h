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
#include "BasePlayerWindow.h"
#include "VideoBoard.h"
#include "OpenFileDialog.h"
#include "PlaylistGraphic.h"

class GraphicLoader {
public:
	GraphicLoader();
	virtual ~GraphicLoader();
	BasePlayerWindow* getBasePlayerWindow();
	VideoBoard* getVideoBoard();
	OpenFileDialog* getOpenDialog();
	PlaylistGraphic* getPlaylistGraphic();
private:
	BasePlayerWindow *basePlayer;
	OpenFileDialog* openWindow;
	VideoBoard *videoBoard;
	PlaylistGraphic* playlist;
};

#endif /* GRAPHICLOADER_H_ */
