/*
 * PlayerWindow.h
 *
 *  Created on: 9.8.2011
 *      Author: xgeier
 */

#ifndef PLAYERWINDOW_H_
#define PLAYERWINDOW_H_

#include <list>
#include <glibmm/ustring.h>
#include <glibmm/main.h>
#include <glibmm/timeval.h>
#include <gdkmm/cursor.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/notebook.h>

#include "../Files/IndigoFile.h"
#include "../Files/FileUtilities.h"
#include "../Interfaces/PlayerSignals.h"
#include "../Interfaces/Callable.h"
#include "../Interfaces/Bridge.h"
#include "../../Settings.h"

class PlayerWindow : public Gtk::Window, public Callable{
public:
	PlayerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~PlayerWindow();
	void setWindowTitle(Glib::ustring title);
	void setListener(PlayerSignals* sig);
	void setBridgePointer(Bridge* windowBridge);
	void changeFullscreen();
	void setVideoBoardSize(int width, int height);
	void call(IndigoPlayerEnum::Command command);
	std::list<IndigoPlayerEnum::Command> getCommandList();
	void setFullscreen(bool full);
private:
	void checkResize();
    typedef void (PlayerWindow::*OFP)(void);
    std::map <IndigoPlayerEnum::Command, OFP> hashTableOfFunction;
    void initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table);
    void unFullscreen();
	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Window* popupWindow;
	Gtk::VBox* capitalPopupVBox;
	Gtk::ToggleButton* video;
	Gtk::ToggleButton* playlist;
	Gtk::ToggleButton* fullScreen;
	Gtk::Notebook* vidListNotebook;
	Gtk::VBox* panel;
	Gtk::VBox* capitalPanel;
	Gtk::VBox* playlistPanel;

	int panelHeight;
	int panelWidth;
	bool stopVPO;
	bool isHideElements;
	bool once;
	bool noHide;
	bool hasPanel;
	bool popupHasPanel;

	void fullScreenClicked();
	void videoPlaylistOpen();
	void dropFiles(const Glib::RefPtr<Gdk::DragContext>&, int, int,	const Gtk::SelectionData&, guint, guint);
	bool keyPress(GdkEventKey* evt);
	bool on_my_motion_notify_event(GdkEventMotion* event);
	bool on_timeout();
	bool leavePopup(GdkEventCrossing* event);
	bool enterPopup(GdkEventCrossing* event);
	void switchPage(GtkNotebookPage* page, guint page_num);
	void quitWindow();

	void removePanel();
	void addPanel();
	void showPopupWindow();
	void removPopupWindow();
	void hideElements();
	void showElements();

	Glib::TimeVal time;
	Glib::TimeVal aktualtime;

	Bridge* windowBridge;
	PlayerSignals *playerSignals;
	Glib::RefPtr<Gdk::Window> gdkCapitalWindow;
	sigc::connection myconnection;
	Gdk::Cursor m_Cursor;
};

#endif /* PLAYERWINDOW_H_ */
