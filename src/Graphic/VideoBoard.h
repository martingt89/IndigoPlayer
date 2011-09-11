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
#include "../Interfaces/Callable.h"
#include "../Interfaces/Bridge.h"
#include "../Settings.h"

class VideoBoard : public Callable{
public:
	VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~VideoBoard();
	void showLogo(bool);
	int getXID();
	void setVideoResolution(int width, int height, bool resize);
	void setBridgePointer(Bridge* windowBridge);
	void call(IndigoPlayerEnum::Command command);
	std::list<IndigoPlayerEnum::Command> getCommandList();

private:
    typedef void (VideoBoard::*OFP)(void);
    std::map <IndigoPlayerEnum::Command, OFP> hashTableOfFunction;
    void initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table);
	void setHalfSize();
	void setOriginalSize();
	void setMaximalizeSize();
	void setFullscreenSize();

	Bridge* windowBridge;
	Gtk::DrawingArea* videoBoard;
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
};

#endif /* VIDEOBOARD_H_ */
