/*
 * VideoBoard.cpp
 *
 *  Created on: 1.8.2011
 *      Author: xgeier
 */

#include "VideoBoard.h"
#include <iostream>

//TODO add set aspect
//TODO set main aspect
//TODO add size mode
VideoBoard::VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder) {
	boardSizeX = 0;
	boardSizeY = 0;
	videoWidth = 0;
	videoHeight = 0;
	showText = true;
	builder->get_widget("videoBoardDrawindBase", videoBoard);
	builder->get_widget("TopArea", upBoard);
	builder->get_widget("DownArea", downBoard);
	builder->get_widget("LeftArea", leftBoard);
	builder->get_widget("RightArea", rightBoard);
	builder->get_widget("FilmBox", filmBox);

	Gdk::Color black;
	Glib::RefPtr<Gdk::Window> win = videoBoard->get_window();
	win->set_background(black);
	win->clear();
	upBoard->get_window()->set_background(black);
	downBoard->get_window()->set_background(black);
	leftBoard->get_window()->set_background(black);
	rightBoard->get_window()->set_background(black);

	videoBoard->signal_expose_event().connect(
			sigc::mem_fun(this, &VideoBoard::on_expose_event));
	image = Gdk::Pixbuf::create_from_file(pathLoader.getPath(IndigoPath::LOGOIMAGE));
	imgX = image->get_width();
	imgY = image->get_height();
	videoBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	upBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	leftBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	downBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	rightBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	videoBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	upBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	downBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	leftBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	rightBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	videoBoard->set_app_paintable(false);
	videoBoard->set_double_buffered(false);
	initHashTable(hashTableOfFunction);
}

VideoBoard::~VideoBoard() {
	delete videoBoard;
	delete upBoard;
	delete downBoard;
	delete leftBoard;
	delete rightBoard;
}
bool VideoBoard::doubleClick(GdkEventButton *ev){
	if(ev->type == GDK_2BUTTON_PRESS )
		windowBridge->changeFullscreen();
	return true;
}
void VideoBoard::showLogo(bool show) {	//TODO rewrite to start playing and stop playing
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

		leftBoard->hide();
		rightBoard->hide();
		upBoard->hide();
		downBoard->hide();

		if (showText)
			image->render_to_drawable(videoBoard->get_window(),
					videoBoard->get_style()->get_black_gc(), 0, 0, x, y, imgX,
					imgY, Gdk::RGB_DITHER_NONE, 0, 0);
	}
	if(!showText && videoWidth != 0 && videoHeight !=0){
		double aspect = (double)videoWidth / videoHeight;
		int boxWidth = filmBox->get_width();
		int boxHeight = filmBox->get_height();

		if((boxWidth / (double)boxHeight) < aspect){
			upBoard->show();
			downBoard->show();
			leftBoard->hide();
			rightBoard->hide();
			//
			int up = (boxHeight - (boxWidth/aspect)) / 2;
			upBoard->set_size_request(0, up);
			downBoard->set_size_request(0, up);
		}
		if((boxWidth / (double)boxHeight) > aspect){
			leftBoard->show();
			rightBoard->show();
			upBoard->hide();
			downBoard->hide();
			//
			int left = (boxWidth - (boxHeight*aspect)) / 2;
			leftBoard->set_size_request(left, 0);
			rightBoard->set_size_request(left, 0);
		}
		if((boxWidth / (double)boxHeight) == aspect){
			leftBoard->hide();
			rightBoard->hide();
			upBoard->hide();
			downBoard->hide();
		}
	}
	return true;
}
void VideoBoard::setHalfSize(){
	if(videoWidth > 0 && videoHeight > 0){
		windowBridge->setResolution(videoWidth/2, videoHeight/2);
	}
}
void VideoBoard::setOriginalSize(){
	if(videoWidth > 0 && videoHeight > 0){
		windowBridge->setResolution(videoWidth,videoHeight);
	}
}
void VideoBoard::setMaximalizeSize(){
	if(videoWidth > 0 && videoHeight > 0){
		windowBridge->setMaximalize(true);
	}
}
void VideoBoard::setFullscreenSize(){
	if(videoWidth > 0 && videoHeight > 0){
		windowBridge->setFullscreen(true);
	}
}
void VideoBoard::setVideoResolution(int width, int height, bool resize){
	//std::cout<<"VideoBoard::setVideoResolution "<<width<<" "<<height<<std::endl;
	videoWidth = width;
	videoHeight = height;
	on_expose_event(NULL);
	if(resize)
		windowBridge->setResolution(width, height);
}
void VideoBoard::setBridgePointer(Bridge* windowBridge){
	this->windowBridge = windowBridge;
}
void VideoBoard::call(IndigoPlayerEnum::Command command){
	if(hashTableOfFunction.find(command) != hashTableOfFunction.end()){
		OFP func = hashTableOfFunction[command];
		(this->*func)();
	}
}
void VideoBoard::initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table){
	table[IndigoPlayerEnum::HALFSIZE] = &VideoBoard::setHalfSize;
	table[IndigoPlayerEnum::ORIGINALSIZE] = &VideoBoard::setOriginalSize;
	table[IndigoPlayerEnum::MAXIMALIZESIZE] = &VideoBoard::setMaximalizeSize;
	table[IndigoPlayerEnum::FULLSCR] = &VideoBoard::setFullscreenSize;
}
std::list<IndigoPlayerEnum::Command> VideoBoard::getCommandList(){
	std::list<IndigoPlayerEnum::Command> list;
	std::map <IndigoPlayerEnum::Command, OFP>::iterator it;
	for(it = hashTableOfFunction.begin(); it != hashTableOfFunction.end(); it++){
		list.push_back(it->first);
	}
	return list;
}
