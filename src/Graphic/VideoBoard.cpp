/*
 * VideoBoard.cpp
 *
 *  Created on: 1.8.2011
 *      Author: xgeier
 */

#include "VideoBoard.h"
#include <iostream>
VideoBoard::VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder, PlayerWindow* wina) {
	playerWindow = wina;
	boardSizeX = 0;
	boardSizeY = 0;
	videoWidth = 0;
	videoHeight = 0;
	showText = true;
	builder->get_widget("videoBoardDrawindBase", videoBoard);
	Gdk::Color black;
	Glib::RefPtr<Gdk::Window> win = videoBoard->get_window();
	win->set_background(black);
	win->clear();
	videoBoard->signal_expose_event().connect(
			sigc::mem_fun(this, &VideoBoard::on_expose_event));
	image = Gdk::Pixbuf::create_from_file(ICONIMAGE);
	imgX = image->get_width();
	imgY = image->get_height();
	videoBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	videoBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	videoBoard->set_app_paintable(false);
	videoBoard->set_double_buffered(false);
	initHashTable(hashTableOfFunction);
}

VideoBoard::~VideoBoard() {
	delete videoBoard;
}
bool VideoBoard::doubleClick(GdkEventButton *ev){
	if(ev->type == GDK_2BUTTON_PRESS )
		playerWindow->changeFullscreen();
	return true;
}
void VideoBoard::showLogo(bool show) {
	showText = show;
	if (showText)
		on_expose_event(NULL);
}

int VideoBoard::getXID() {
	return GDK_WINDOW_XID(Glib::unwrap(videoBoard->get_window()));
	return 0;
}

bool VideoBoard::on_expose_event(GdkEventExpose* ev) {
	int x = videoBoard->get_window()->get_width();
	int y = videoBoard->get_window()->get_height();
	if (showText || (boardSizeX != x || boardSizeY != y)) {
		boardSizeX = x;
		boardSizeY = y;
		videoBoard->get_window()->clear();
		x = (x - imgX) / 2;
		y = (y - imgY) / 2;

		if (showText)
			image->render_to_drawable(videoBoard->get_window(),
					videoBoard->get_style()->get_black_gc(), 0, 0, x, y, imgX,
					imgY, Gdk::RGB_DITHER_NONE, 0, 0);
	}
	return true;
}
void VideoBoard::setHalfSize(){
	if(videoWidth > 0 && videoHeight > 0){
		playerWindow->setfullscreen(false);
		playerWindow->unmaximize();
		playerWindow->setVideoBoardSize(100,100);
		playerWindow->setVideoBoardSize(videoWidth/2,videoHeight/2);
	}
}
void VideoBoard::setFullSize(){
	if(videoWidth > 0 && videoHeight > 0){
		playerWindow->setfullscreen(false);
		playerWindow->unmaximize();
		playerWindow->setVideoBoardSize(100,100);
		playerWindow->setVideoBoardSize(videoWidth,videoHeight);
	}
}
void VideoBoard::setMaximalizeSize(){
	if(videoWidth > 0 && videoHeight > 0){
		playerWindow->setfullscreen(false);
		playerWindow->maximize();
		//playerWindow->setVideoBoardSize(videoWidth*2,videoHeight*2);
	}
}
void VideoBoard::setFullscreenSize(){
	if(videoWidth > 0 && videoHeight > 0){
		playerWindow->setfullscreen(true);
	}
}
void VideoBoard::setVideoResolution(int width, int height, bool resize){
	videoWidth = width;
	videoHeight = height;
	if(resize)
		playerWindow->setVideoBoardSize(width,height);
}
void VideoBoard::call(IndigoPlayerCommand::Command command){
	if(hashTableOfFunction.find(command) != hashTableOfFunction.end()){
		OFP func = hashTableOfFunction[command];
		(this->*func)();
	}
}
void VideoBoard::initHashTable(std::map <IndigoPlayerCommand::Command, OFP> &table){
	table[IndigoPlayerCommand::HALFSIZE] = &VideoBoard::setHalfSize;
	table[IndigoPlayerCommand::ORIGINALSIZE] = &VideoBoard::setFullSize;
	table[IndigoPlayerCommand::MAXIMALIZESIZE] = &VideoBoard::setMaximalizeSize;
	table[IndigoPlayerCommand::FULLSCR] = &VideoBoard::setFullscreenSize;
}
std::list<IndigoPlayerCommand::Command> VideoBoard::getCommandList(){
	std::list<IndigoPlayerCommand::Command> list;
	std::map <IndigoPlayerCommand::Command, OFP>::iterator it;
	for(it = hashTableOfFunction.begin(); it != hashTableOfFunction.end(); it++){
		list.push_back(it->first);
	}
	return list;
}
