/*
 * GraphicLoader.h
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 */

#ifndef GRAPHICLOADER_H_
#define GRAPHICLOADER_H_

#include <gtkmm/builder.h>
#include <iostream>
#include "../../Settings.h"
#include "BasePlayerWindow.h"
#include "VideoBoard.h"

class GraphicLoader {
public:
	GraphicLoader();
	virtual ~GraphicLoader();
	BasePlayerWindow* getBasePlayerWindow();
	VideoBoard* getVideoBoard();
private:
	BasePlayerWindow *basePlayer;
	VideoBoard *videoBoard;
};

#endif /* GRAPHICLOADER_H_ */
