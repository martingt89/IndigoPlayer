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
#include "PlayerWindow.h"
#include "Display.h"

class VideoBoard {
public:
	VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder, PlayerWindow* win);
	virtual ~VideoBoard();
	void showLogo(bool);
	int getXID();
	void resize(int x, int y);
private:
	Gtk::DrawingArea* videoBoard;
	//IDisplay* videoBoard;
	Glib::RefPtr<Gdk::Pixbuf> image;
	Glib::RefPtr< Gdk::Window > mojko;
	bool on_expose_event(GdkEventExpose* ev);
	bool on_timeout();
	bool doubleClick(GdkEventButton *ev);
	int imgX;
	int imgY;
	int boardSizeX;
	int boardSizeY;
	bool showText;
	PlayerWindow* playerWindow;
};

#endif /* VIDEOBOARD_H_ */
