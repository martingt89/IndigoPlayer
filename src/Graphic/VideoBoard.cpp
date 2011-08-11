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
	showText = true;
	builder->get_widget("videoBoardDrawindBase", videoBoard);
//builder->get_widget_derived("videoBoardDrawindBase", videoBoard);
	Gdk::Color black;
	Glib::RefPtr<Gdk::Window> win = videoBoard->get_window();
	win->set_background(black);
	win->clear();
	videoBoard->signal_expose_event().connect(
			sigc::mem_fun(this, &VideoBoard::on_expose_event));
	image = Gdk::Pixbuf::create_from_file("myimage.svg");
	imgX = image->get_width();
	imgY = image->get_height();
	videoBoard->add_events(Gdk::BUTTON_PRESS_MASK);
	videoBoard->signal_button_press_event().connect(sigc::mem_fun(this, &VideoBoard::doubleClick));
	videoBoard->set_app_paintable(false);
	videoBoard->set_double_buffered(false);
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
}

bool VideoBoard::on_timeout() {
	std::cout<<"on_timeout"<<std::endl;
	videoBoard->get_window()->clear();
	int x = videoBoard->get_window()->get_width();
	int y = videoBoard->get_window()->get_height();
	x = (x - imgX) / 2;
	y = (y - imgY) / 2;
	if (showText)
		image->render_to_drawable(videoBoard->get_window(),
				videoBoard->get_style()->get_black_gc(), 0, 0, x, y, imgX, imgY,
				Gdk::RGB_DITHER_NONE, 0, 0);
	return false;
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
//		Glib::signal_timeout().connect(
//				sigc::mem_fun(*this, &VideoBoard::on_timeout), 100);
	}
	return true;
}
void VideoBoard::resize(int x, int y){
	//videoBoard->get_window()->resize(x,y);
	playerWindow->setVideoBoardSize(x,y);
}
