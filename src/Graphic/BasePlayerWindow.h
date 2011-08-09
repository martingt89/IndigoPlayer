/*
 * BasePlayerWindow.h
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 */

#ifndef BASEPLAYERWINDOW_H_
#define BASEPLAYERWINDOW_H_

#include <gtkmm/button.h>
#include <gtkmm/scale.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/separator.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/notebook.h>
#include <gtkmm/frame.h>

#include <gdk/gdkx.h>

#include "../Interfaces/PlayerSignals.h"
#include "../../Settings.h"
#include "../Files/IndigoFile.h"
#include "../Files/FileUtilities.h"

class BasePlayerWindow: public Gtk::Window {
public:
	BasePlayerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~BasePlayerWindow();
	void setSignalListener(PlayerSignals *ps);
	void setWindowTitle(Glib::ustring);
	void setDuration(int);
	void setPosition(int);
	void clearTime();
	void setAudioLevel(double level);
	double getAudioLevel();
	void openFullscreen();
	void closeFullscreen();
	void popPlayButton();
	bool isFullscreen();
private:
	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* forward;
	Gtk::Button* backward;
	Gtk::Button* cancel;
	Gtk::Button* fullScreen;
	Gtk::Button* kill;
	Gtk::Button* backInFile;
	Gtk::Button* thisOptions;
	Gtk::Button* open;
	Gtk::ToggleButton* playStop;
	Gtk::ToggleButton* soundMute;
	Gtk::HScale* timeline;
	Gtk::HScale* sound;
	Gtk::Label* time;
	Gtk::VBox* panel;
	Gtk::VBox* capitalPanel;
	Gtk::HSeparator* separator;
	Gtk::Adjustment timelineAdj;
	Gtk::Adjustment soundAdj;

	Gtk::ToggleButton* video;
	Gtk::ToggleButton* playlist;
	Gtk::Notebook* notebook;

	Gtk::Window* popupWindow;
	Gtk::VBox* capitalPopupVBox;

	PlayerSignals *playerSignals;
	//
	int duration;
	int position;

	int active;
	bool stopVPO;

	bool timeline_changed_signal;
	bool sound_changed_signal;
	bool playStopSignal;
	bool isFull;
	Glib::ustring getTimeText(int position, int duration);

	void on_toggledPlay_clicked();
	void on_toggledSound_clicked();
	void forward_clicked();
	void backward_clicked();
	void cancel_clicked();
	void fullScreen_clicked();
	void thisOptions_clicked();
	void open_clicked();
	void backInFile_clicked();
	void sound_changed();
	void timeline_changed();
	void videoPlaylistOpen();
	void on_drop_files(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
			const Gtk::SelectionData& selection_data, guint info, guint time);
	bool on_button_clicked(GdkEventKey* evt);
};
#endif /* BASEPLAYERWINDOW_H_ */
