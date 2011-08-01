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

#include "../Interfaces/PlayerSignals.h"
#include "../../Settings.h"

class BasePlayerWindow  : public Gtk::Window{
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
private:
	 Glib::RefPtr<Gtk::Builder> m_refGlade;
	 Gtk::Button* forward;
	 Gtk::Button* backward;
	 Gtk::Button* cancel;
	 Gtk::Button* fullScreen;
	 Gtk::Button* kill;
	 Gtk::Button* backInFile;
	 Gtk::Button* thisOptions;
	 Gtk::ToggleButton* playStop;
	 Gtk::ToggleButton* soundMute;
	 Gtk::HScale* timeline;
	 Gtk::HScale* sound;
	 Gtk::Label* time;
	 Gtk::VBox* panel;
	 Gtk::HSeparator* separator;
	 Gtk::Adjustment timelineAdj;
	 Gtk::Adjustment soundAdj;

	 Gtk::ToggleButton* video;
	 Gtk::ToggleButton* playlist;
	 Gtk::ToggleButton* open;
	 Gtk::Notebook* notebook;

	 PlayerSignals *playerSignals;
	 //
	 int duration;
	 int position;

	 int active;
	 bool stopVPO;
	 Glib::ustring getTimeText(int position, int duration);

	 void on_toggledPlay_clicked();
	 void on_toggledSound_clicked();
	 void forward_clicked();
	 void backward_clicked();
	 void cancel_clicked();
	 void fullScreen_clicked();
	 void thisOptions_clicked();
	 void playlist_clicked();
	 void open_clicked();
	 void backInFile_clicked();
	 void sound_changed();
	 void timeline_changed();
	 void videoPlaylistOpen();

	 bool timeline_changed_signal;
	 bool sound_changed_signal;
};

#endif /* BASEPLAYERWINDOW_H_ */
