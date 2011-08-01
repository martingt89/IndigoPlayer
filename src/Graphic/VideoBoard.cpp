/*
 * VideoBoard.cpp
 *
 *  Created on: 1.8.2011
 *      Author: xgeier
 */

#include "VideoBoard.h"

VideoBoard::VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder) {
	builder->get_widget("videoBoardDrawindBase", videoBoard);
	Gdk::Color black;

	Glib::RefPtr<Gdk::Window> win = videoBoard->get_window();
	win->set_background(black);
	win->clear();
	videoBoard->signal_expose_event().connect(sigc::mem_fun(this, &VideoBoard::on_expose_event));
	std::cout<<this->getXID()<<std::endl;
	image = Gdk::Pixbuf::create_from_file("myimage.svg");
}

VideoBoard::~VideoBoard() {
	// TODO Auto-generated destructor stub
}

void VideoBoard::showPlay(bool show) {

}

int VideoBoard::getXID() {
	return GDK_WINDOW_XID(Glib::unwrap(videoBoard->get_window()));
}

bool VideoBoard::on_expose_event(GdkEventExpose* ev)
{
	videoBoard->get_window()->clear();

image->render_to_drawable(videoBoard->get_window(), videoBoard->get_style()->get_black_gc(),
0, 0, 100, 80, image->get_width(), image->get_height(), // draw the whole image (from 0,0 to the full width,height) at 100,80 in the window
Gdk::RGB_DITHER_NONE, 0, 0);

return true;
}
