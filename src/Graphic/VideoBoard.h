/*
 * VideoBoard.h
 *
 *  Created on: 1.8.2011
 *      Author: xgeier
 */

#ifndef VIDEOBOARD_H_
#define VIDEOBOARD_H_

#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include <gtkmm.h>
#include <gdk/gdkx.h>
#include <iostream>

class VideoBoard {
public:
	VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~VideoBoard();
	void showPlay(bool);
	int getXID();
private:
	Gtk::DrawingArea* videoBoard;
	Gtk::Image* imageBoard;
	Glib::RefPtr<Gdk::Pixbuf> image;
	bool on_expose_event(GdkEventExpose* ev);
};

#endif /* VIDEOBOARD_H_ */
