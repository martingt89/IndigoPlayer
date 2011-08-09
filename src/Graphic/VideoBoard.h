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
#include <glibmm/ustring.h>
#include <gdk/gdkx.h>
#include <giomm/file.h>
#include "../Interfaces/PlayerSignals.h"

class VideoBoard {
public:
	VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~VideoBoard();
	void showPlay(bool);
	int getXID();
private:
	Gtk::DrawingArea* videoBoard;
	Glib::RefPtr<Gdk::Pixbuf> image;
	Glib::RefPtr< Gdk::Window > mojko;
	bool on_expose_event(GdkEventExpose* ev);
	bool on_timeout();
	int imgX;
	int imgY;
	int boardSizeX;
	int boardSizeY;
	bool showText;
};

#endif /* VIDEOBOARD_H_ */
