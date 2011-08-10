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

#include "../Interfaces/PlayerSignals.h"
#include "../../Settings.h"
#include "../Files/IndigoFile.h"
#include "../Files/FileUtilities.h"

class ControlPanel{
public:
	ControlPanel(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~ControlPanel();
	void setListener(PlayerSignals *ps);
	void setDuration(int);
	void setPosition(int);
	void clearTime();
	void setAudioLevel(double level);
	double getAudioLevel();
	void popPlayButton();
	void pushPlayButton();
private:
	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* forward;
	Gtk::Button* backward;
	Gtk::Button* cancel;
	Gtk::Button* backInFile;
	Gtk::Button* open;
	Gtk::ToggleButton* playStop;
	Gtk::ToggleButton* soundMute;
	Gtk::Label* time;
	Gtk::Adjustment* timelineAdj;
	Gtk::Adjustment* soundAdj;
	Gtk::HScale* sound;
	Gtk::HScale* timeline;

	PlayerSignals *playerSignals;
	//
	int duration;
	int position;

	bool timeline_changed_signal;
	bool sound_changed_signal;
	bool playStopSignal;
	Glib::ustring getTimeText(int position, int duration);

	void on_toggledPlay_clicked();
	void on_toggledSound_clicked();
	void forward_clicked();
	void backward_clicked();
	void cancel_clicked();
	void thisOptions_clicked();
	void open_clicked();
	void backInFile_clicked();
	void sound_changed();
	void timeline_changed();
};
#endif /* BASEPLAYERWINDOW_H_ */
