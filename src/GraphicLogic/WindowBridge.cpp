/*
 * WindowBridge.cpp
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#include "WindowBridge.h"

WindowBridge::WindowBridge() {

}

WindowBridge::~WindowBridge() {
	// TODO Auto-generated destructor stub
}
void WindowBridge::addCallable(Callable* callable){
	shortKeys.addList(callable, callable->getCommandList());
}
void WindowBridge::setPlayerWindow(PlayerWindow *playerWin) {
	this->playerWin = playerWin;
	shortKeys.addList(this->playerWin, this->playerWin->getCommandList());
	this->playerWin->setBridgePointer(this);
}
void WindowBridge::setPlaylist(Playlist *playlist) {
	this->playlist = playlist;
}
void WindowBridge::setVideoBoard(VideoBoard* board) {
	this->board = board;
	shortKeys.addList(this->board, this->board->getCommandList());
	this->board->setBridgePointer(this);
}
void WindowBridge::setOpenDialog(OpenFileDialog* dialog) {
	this->dialog = dialog;
}
void WindowBridge::setControlPanel(ControlPanel* control) {
	this->control = control;
	shortKeys.addList(this->control, this->control->getCommandList());
	this->control->setBridgePointer(this);
}
void WindowBridge::setThisOptions(ThisOptions* opt) {
	this->opt = opt;
}
void WindowBridge::setThisOptionsLoad(ThisOptionsLoad* optLoad) {
	this->optLoad = optLoad;
}
//==================================================================
void WindowBridge::clickOpenButton() {
	dialog->showOn();
}
void WindowBridge::clickThisOptionsButton() {
	opt->show();
}
void WindowBridge::setResolution(int width, int height) {
	playerWin->setVideoBoardSize(width, height);
}
void WindowBridge::changeFullscreen() {
	playerWin->changeFullscreen();
}
void WindowBridge::setFullscreen(bool full) {
	playerWin->setFullscreen(full);
}
void WindowBridge::setMaximalize(bool max) {
	if (max) {
		playerWin->setFullscreen(false);
		playerWin->maximize();
	} else {
		playerWin->setFullscreen(false);
		playerWin->unmaximize();
	}
}
void WindowBridge::keyPressed(int control, int keyVal, unsigned short hardwareKey) {
//	std::cout<<"void WindowBridge::keyPressed(int control, int keyVal, unsigned short hardwareKey) "<<keyVal<<" "<<hardwareKey<<std::endl;
	IndigoPlayerEnum::ControlKey key = IndigoPlayerEnum::NONE;
	if (control & Gdk::MOD1_MASK)
		key = IndigoPlayerEnum::ALT;
	else if (control & Gdk::CONTROL_MASK)
		key = IndigoPlayerEnum::CTRL;
	else if (control & Gdk::SHIFT_MASK)
		key = IndigoPlayerEnum::SHIFT;
	else if (control & Gdk::LOCK_MASK)
		key = IndigoPlayerEnum::CAPSLOCK;

	shortKeys.keyPressed(key, keyVal, hardwareKey);
}
