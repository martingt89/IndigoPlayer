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
#include <gtkmm/progressbar.h>
#include <gtkmm/spinner.h>
#include <gtkmm/image.h>

#include "../Interfaces/PlayerSignals.h"
#include "../Interfaces/Callable.h"
#include "../Interfaces/Bridge.h"
#include "../Files/IndigoFile.h"
#include "../Files/FileUtilities.h"
#include "../GraphicLogic/GraphicPathLoader.h"
#include "../Settings.h"

class ControlPanel : public Callable{
public:
	ControlPanel(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~ControlPanel();
	void setListener(PlayerSignals *ps);
	void setBridgePointer(Bridge* windowBridge);
	void setDuration(int);
	void setPosition(int);
	void clearTime();
	void setAudioLevel(double level);
	double getAudioLevel();
	int getTime();
	void popPlayButton();
	void pushPlayButton();
	bool isMute();
	void hideLoading();
	void showLoading();
	void call(IndigoPlayerEnum::Command command);
	std::list<IndigoPlayerEnum::Command> getCommandList();
private:
	typedef void (ControlPanel::*OFP)(void);
	std::map <IndigoPlayerEnum::Command, OFP> hashTableOfFunction;
	void initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table);

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* forward;
	Gtk::Button* backward;
	Gtk::Button* cancel;
	Gtk::Button* backInFile;
	Gtk::Button* open;
	Gtk::Button* thisOptionsButton;
	Gtk::Button* optionsButton;

	Gtk::ToggleButton* playStop;
	Gtk::ToggleButton* soundMute;
	Gtk::Label* time;
	Gtk::Adjustment* soundAdj;
	Gtk::HScale* sound;
	Gtk::ProgressBar* timeProgress;
	Gtk::Spinner* loadProgress;

	Gtk::Window toolTipWindow;
	Gtk::Label* toolTipLabel;

	Gtk::Image playImage;
	Gtk::Image pauseImage;
	Gtk::Image soundImage;
	Gtk::Image muteImage;

	GraphicPathLoader pathLoader;

	PlayerSignals *playerSignals;
	Bridge* windowBridge;
	//
	int duration;
	int position;

	bool timeline_changed_signal;
	bool sound_changed_signal;
	bool playStopSignal;
	bool aktualizeTextSignal;
	Glib::ustring getTimeText(int position, int duration);
	bool toolTipShow(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
	Glib::ustring timeToWellText(int time);
	void playStopSoftPressed();
	void muteUnmuteSoftPressed();

	bool timeProgressClicked(GdkEventButton* event);
	void playToggleClicked();
	void soundToggleClicked();
	void forwardClicked();
	void backwardClicked();
	void cancelClicked();
	void thisOptionsClicked();
	void optionsClicked();
	void openButtonClicked();
	void rewindButtonClicked();
	void soundLevelChanged();
	void timelineChanged();
};
#endif /* BASEPLAYERWINDOW_H_ */
