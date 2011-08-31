/*
 * WindowBridge.cpp
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#include "WindowBridge.h"

WindowBridge::WindowBridge() {
	std::map<std::pair<int, int>, IndigoPlayerCommand::Command> table;
	table[std::make_pair(8208,102)] = IndigoPlayerCommand::FULLUNFULLSCR;
	table[std::make_pair(8208,109)] = IndigoPlayerCommand::MUTEUNMUTE;
	shortKeys.setConvertTable(table);
	std::map<short unsigned, IndigoPlayerCommand::Command> hTable;
	hTable[9] = IndigoPlayerCommand::UNFULLSCR;
	hTable[10] = IndigoPlayerCommand::HALFSIZE;
	hTable[11] = IndigoPlayerCommand::ORIGINALSIZE;
	hTable[12] = IndigoPlayerCommand::MAXIMALIZESIZE;
	hTable[13] = IndigoPlayerCommand::FULLSCR;
	hTable[65] = IndigoPlayerCommand::PLAYSTOPBUT;
	shortKeys.setHardwareConvertTable(hTable);
}

WindowBridge::~WindowBridge() {
	// TODO Auto-generated destructor stub
}

void WindowBridge::setPlayerWindow(PlayerWindow *playerWin){
	this->playerWin = playerWin;
	shortKeys.addList(this->playerWin, this->playerWin->getCommandList());
	this->playerWin->setBridgePointer(this);
}
void WindowBridge::setPlaylist(Playlist *playlist){
	this->playlist = playlist;
}
void WindowBridge::setVideoBoard(VideoBoard* board){
	this->board = board;
	shortKeys.addList(this->board,this->board->getCommandList());
	this->board->setBridgePointer(this);
}
void WindowBridge::setOpenDialog(OpenFileDialog* dialog){
	this->dialog = dialog;
}
void WindowBridge::setControlPanel(ControlPanel* control){
	this->control = control;
	shortKeys.addList(this->control, this->control->getCommandList());
	this->control->setBridgePointer(this);
}
void WindowBridge::setThisOptions(ThisOptions* opt){
	this->opt = opt;
}
void WindowBridge::setThisOptionsLoad(ThisOptionsLoad* optLoad){
	this->optLoad = optLoad;
}
//==================================================================
void WindowBridge::clickOpenButton(){
	dialog->show();
}
void WindowBridge::clickThisOptionsButton(){
	opt->show();
}
void WindowBridge::setResolution(int width, int height){
	playerWin->setVideoBoardSize(width, height);
}
void WindowBridge::changeFullscreen(){
	playerWin->changeFullscreen();
}
void WindowBridge::setFullscreen(bool full){
	playerWin->setFullscreen(full);
}
void WindowBridge::setMaximalize(bool max){
	if(max){
		playerWin->setFullscreen(false);
		playerWin->maximize();
	}else{
		playerWin->setFullscreen(false);
		playerWin->unmaximize();
	}
}
void WindowBridge::keyPressed(int control, int keyVal, unsigned short hardwareKey){
//	std::cout<<control<<" "<<keyVal<<" "<<hardwareKey<<std::endl;
//	if(control & Gdk::SHIFT_MASK)
//		std::cout<<"Press: Shift"<<std::endl;
//	if(control & Gdk::LOCK_MASK)
//		std::cout<<"Press: Lock"<<std::endl;
//	if(control & Gdk::CONTROL_MASK)
//		std::cout<<"Press: Ctrl"<<std::endl;
	shortKeys.keyPressed(control, keyVal, hardwareKey);
}
