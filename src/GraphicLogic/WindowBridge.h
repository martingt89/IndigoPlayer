/*
 * WindowBridge.h
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#ifndef WINDOWBRIDGE_H_
#define WINDOWBRIDGE_H_

#include <iostream>
//#include <gdkmm/window.h>

#include "../Interfaces/Bridge.h"
#include "../Interfaces/Callable.h"
#include "../Graphic/PlayerWindow.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/OpenFileDialog.h"
#include "../Graphic/ControlPanel.h"
#include "../Graphic/ThisOptions.h"
#include "../Graphic/ThisOptionsLoad.h"
#include "../GraphicLogic/Playlist.h"
#include "../Player/ShortKeys.h"
#include "../../EnumTypes.h"

class WindowBridge : public Bridge{
public:
	WindowBridge();
	virtual ~WindowBridge();

	void setPlayerWindow(PlayerWindow *playerWin);
	void setPlaylist(Playlist *playlist);
	void setVideoBoard(VideoBoard* board);
	void setOpenDialog(OpenFileDialog* dialog);
	void setControlPanel(ControlPanel* control);
	void setThisOptions(ThisOptions* opt);
	void setThisOptionsLoad(ThisOptionsLoad* optLoad);
	//================================================
	void clickOpenButton();
	void clickThisOptionsButton();
	void setResolution(int width, int height);
	void changeFullscreen();
	void setFullscreen(bool);
	void setMaximalize(bool max);
	void keyPressed(int control, int keyVal, unsigned short hardwareKey);
private:
	PlayerWindow *playerWin;
	Playlist *playlist;
	VideoBoard* board;
	OpenFileDialog* dialog;
	ControlPanel* control;
	ThisOptions* opt;
	ThisOptionsLoad* optLoad;
	//================================================
	ShortKeys shortKeys;
};

#endif /* WINDOWBRIDGE_H_ */
