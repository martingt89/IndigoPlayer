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
#include "PlayerWindow.h"
#include "../Interfaces/PlayerSignals.h"
#include "../Interfaces/Callable.h"

class VideoBoard : public Callable{
public:
	VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder, PlayerWindow* win);
	virtual ~VideoBoard();
	void showLogo(bool);
	int getXID();
	//void resize(int x, int y);
	void setVideoResolution(int width, int height, bool resize);
	void setHalfSize();
	void setFullSize();
	void setMaximalizeSize();
	void setFullscreenSize();
	void call(IndigoPlayerCommand::Command command);
	std::list<IndigoPlayerCommand::Command> getCommandList();
private:
    typedef void (VideoBoard::*OFP)(void);
    std::map <IndigoPlayerCommand::Command, OFP> hashTableOfFunction;
    void initHashTable(std::map <IndigoPlayerCommand::Command, OFP> &table);

	Gtk::DrawingArea* videoBoard;
	//IDisplay* videoBoard;
	Glib::RefPtr<Gdk::Pixbuf> image;
	Glib::RefPtr< Gdk::Window > mojko;
	bool on_expose_event(GdkEventExpose* ev);
	bool doubleClick(GdkEventButton *ev);
	int imgX;
	int imgY;
	int boardSizeX;
	int boardSizeY;
	int videoWidth;
	int videoHeight;
	bool showText;
	PlayerWindow* playerWindow;
};

#endif /* VIDEOBOARD_H_ */
