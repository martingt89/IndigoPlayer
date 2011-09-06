/*
 * ThisOptionsLoad.h
 *
 *  Created on: 22.8.2011
 *      Author: xgeier
 */

#ifndef THISOPTIONSLOAD_H_
#define THISOPTIONSLOAD_H_
#include <gtkmm/builder.h>
#include <gtkmm/scale.h>
#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/combobox.h>
#include "../MyWidget/MyComboBox.h"
#include "../Interfaces/PlayerSignals.h"
#include "../MyWidget/FileChoosers.h"
#include <list>
class ThisOptionsLoad {
public:
	ThisOptionsLoad(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ThisOptionsLoad();
	void addSubtitles(Glib::ustring, bool play);
	void addSubtitleList(std::list<Glib::ustring> files, bool firstShow = false);
	void addAudioList(std::list<Glib::ustring> files, bool firstShow = false);
	void setListener(PlayerSignals *sig);
	void runPlaying();
	void stopPlaying();
	void setAktualSubtitles(Glib::ustring name);
	void setAktualAudio(Glib::ustring name);
private:
	void subStraemChanged();
	void subButtonClicked();
	void audButtonClicked();
	void audStraemChanged();
	Gtk::Button* audioLoad;
	Gtk::Button* subtitleLoad;
	Gtk::SpinButton* audioDelay;
	Gtk::SpinButton* subtitleDelay;
	Gtk::ComboBox* videoStream;
	Gtk::ComboBox* audioStream;
	Gtk::ComboBox* subtitleStream;

	MyComboBox* myVideoStream;
	MyComboBox* myAudioStream;
	MyComboBox* mySubtitleStream;
	PlayerSignals * playerSignal;
};

#endif /* THISOPTIONSLOAD_H_ */
