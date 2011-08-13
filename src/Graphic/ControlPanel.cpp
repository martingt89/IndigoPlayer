/*
 * BasePlayerWindow.cpp
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 *
 * Nacitanie zakladneho okna, zakladna logika grafiky
 * pri aktivacii prostredia, vola metody interfejsu
 */

#include "ControlPanel.h"

#include <iostream>

ControlPanel::ControlPanel(const Glib::RefPtr<Gtk::Builder>& refGlade){
	m_refGlade = refGlade;
	playerSignals = NULL;
	timeline_changed_signal = true;
	sound_changed_signal = true;
	playStopSignal = true;
	aktualizeTextSignal = true;

	m_refGlade->get_widget("ForwardButtonBase", forward);
	m_refGlade->get_widget("BackwardButtonBase", backward);
	m_refGlade->get_widget("PlayStopTButtonBase", playStop);
	m_refGlade->get_widget("CanceButtonBase", cancel);
	m_refGlade->get_widget("MuteTButtonBase", soundMute);
	m_refGlade->get_widget("BackInFileButtonBase", backInFile);
	m_refGlade->get_widget("TimeProgressBase", timeProgress);

	m_refGlade->get_widget("TimeLabelBase", time);
	m_refGlade->get_widget("OpenButtonBase", open);
	m_refGlade->get_widget("SoundHScaleBase", sound);

	soundAdj = new Gtk::Adjustment(100,0,100);

	this->clearTime();
	sound->set_adjustment(*soundAdj);
	timeProgress->add_events(Gdk::BUTTON_PRESS_MASK);
	playStop->signal_toggled().connect(sigc::mem_fun(this, &ControlPanel::on_toggledPlay_clicked));
	soundMute->signal_toggled().connect(sigc::mem_fun(this, &ControlPanel::on_toggledSound_clicked));
	forward->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::forward_clicked));
	backward->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::backward_clicked));
	cancel->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::cancel_clicked));
	open->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::open_clicked));
	backInFile->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::backInFile_clicked));
	soundAdj->signal_value_changed().connect(sigc::mem_fun(this, &ControlPanel::sound_changed));
	timeProgress->signal_button_press_event().connect(sigc::mem_fun(this, &ControlPanel::timeProgressClicked));
}
bool ControlPanel::timeProgressClicked(GdkEventButton* event){
	if(event->type == GDK_BUTTON_PRESS){
		if(duration > -1){
			double pos = (1.0/duration)*(int)((event->x / (double)timeProgress->get_width())*duration);
			timeProgress->set_fraction(pos);
			timeline_changed();
		}
	}
	return true;
}
void ControlPanel::clearTime() {
	duration = -1;
	position = -1;
	time->set_text(getTimeText(position, duration));
	timeProgress->set_fraction(0);
}
void ControlPanel::setDuration(int seconds) {
	duration = seconds;
	position = 0;
	time->set_text(getTimeText(position, duration)); //TODO //prepisat na multi threading
	timeline_changed_signal = false;
	timeline_changed_signal = true;
}
void ControlPanel::setPosition(int seconds) {
	position = seconds;
	if (duration >= 0) {
		time->set_text(getTimeText(position, duration)); //TODO //prepisat na multi threading
		if(aktualizeTextSignal){
			timeline_changed_signal = false;
			timeProgress->set_fraction(position/(double)duration);
			timeline_changed_signal = true;
		}
	}
}
void ControlPanel::setAudioLevel(double level) {
	sound_changed_signal = false;
	soundAdj->set_value(level); //TODO //prepisat na multi threading
	sound_changed_signal = true;
}
double ControlPanel::getAudioLevel() {
	return soundAdj->get_value(); //TODO //prepisat na multi threading
}
int ControlPanel::getTime(){
	return timeProgress->get_fraction()*duration;
}
bool ControlPanel::isMute() {
	return soundMute->get_active();
}
void ControlPanel::popPlayButton() {
	playStopSignal = false;
	playStop->set_active(false);
	playStopSignal = true;
}
void ControlPanel::pushPlayButton() {
	playStopSignal = false;
	playStop->set_active(true);
	playStopSignal = true;
}
void ControlPanel::setListener(PlayerSignals *ps) {
	playerSignals = ps;
}
//---------------------private functions---------------------------//
Glib::ustring ControlPanel::getTimeText(int position, int duration) {
	if (position < 0 || duration < 0) {
		return ("--:-- / --:--");
	}
	int min = position / 60;
	int sec = position % 60;
	int min10 = min / 10;
	min = min % 10;
	int sec10 = sec / 10;
	sec = sec % 10;

	Glib::ustring time = Glib::ustring::format(min10) + Glib::ustring::format(min) + ":"
			+ Glib::ustring::format(sec10) + Glib::ustring::format(sec) + " / ";

	min = duration / 60;
	sec = duration % 60;
	min10 = min / 10;
	min = min % 10;
	sec10 = sec / 10;
	sec = sec % 10;

	time += Glib::ustring::format(min10) + Glib::ustring::format(min) + ":" + Glib::ustring::format(sec10)
			+ Glib::ustring::format(sec);
	return time;
}
void ControlPanel::sound_changed() {
	if (playerSignals != 0 && sound_changed_signal)
		playerSignals->changeSoundLevel();
}
void ControlPanel::timeline_changed() {
	if(timeline_changed_signal){
		aktualizeTextSignal = false;
		setPosition(getTime());
		aktualizeTextSignal = true;
		if (playerSignals != 0)
			playerSignals->changeTimeLine();
	}
}
void ControlPanel::open_clicked() {
	if (playerSignals != 0)
		playerSignals->clickOpen();
}
void ControlPanel::forward_clicked() {
	if (playerSignals != 0)
		playerSignals->clickForward();
}
void ControlPanel::backward_clicked() {
	if (playerSignals != 0)
		playerSignals->clickBackward();
}
void ControlPanel::cancel_clicked() {
	if (playerSignals != 0)
		playerSignals->clickCancel();
}
void ControlPanel::thisOptions_clicked() {
	if (playerSignals != 0)
		playerSignals->clickThisOptions();
}
void ControlPanel::backInFile_clicked() {
	if (playerSignals != 0)
		playerSignals->clickRewind();
}
void ControlPanel::on_toggledPlay_clicked() {
	if (playerSignals != 0 && playStopSignal) {
		if (playStop->get_active() == true)
			playerSignals->clickPlay();
		else
			playerSignals->clickPause();
	}
}
void ControlPanel::on_toggledSound_clicked() {
	if (playerSignals != 0) {
		if (soundMute->get_active() == true) {
			playerSignals->clickMute();
			sound->set_sensitive(false); //TODO //prepisat na multi threading
		} else {
			playerSignals->clickSound();
			sound->set_sensitive(true); //TODO //prepisat na multi threading
		}
	}
}


ControlPanel::~ControlPanel() {
	delete forward;
	delete backward;
	delete cancel;
	delete backInFile;
	delete open;
	delete playStop;
	delete soundMute;
	delete sound;
	delete time;
}
