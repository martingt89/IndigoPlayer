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

ControlPanel::ControlPanel(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		toolTipWindow(Gtk::WINDOW_POPUP) {
	m_refGlade = refGlade;
	playerSignals = NULL;
	windowBridge = NULL;
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
	m_refGlade->get_widget("ThisOptionsButtonBase", thisOptionsButton);

	m_refGlade->get_widget("TimeLabelBase", time);
	m_refGlade->get_widget("LoadProgress", loadProgress);

	m_refGlade->get_widget("OpenButtonBase", open);
	m_refGlade->get_widget("SoundHScaleBase", sound);

	playImage.set(pathLoader.getPath(IndigoPath::PLAYIMAGE));
	pauseImage.set(pathLoader.getPath(IndigoPath::PAUSEIMAG));
	soundImage.set(pathLoader.getPath(IndigoPath::SOUNDIMAG));
	muteImage.set(pathLoader.getPath(IndigoPath::MUTEIMAGE));

	soundAdj = new Gtk::Adjustment(100, 0, 100);
	soundMute->set_image(soundImage);

	this->clearTime();
	sound->set_adjustment(*soundAdj);
	timeProgress->add_events(Gdk::BUTTON_PRESS_MASK);

	timeProgress->set_tooltip_window(toolTipWindow);
	toolTipLabel = Gtk::manage(new Gtk::Label(""));
	toolTipLabel->show();
	toolTipWindow.set_default_size(50, 25);
	toolTipWindow.add(*toolTipLabel);

	playStop->set_image(playImage);

	playStop->signal_toggled().connect(sigc::mem_fun(this, &ControlPanel::playToggleClicked));
	soundMute->signal_toggled().connect(sigc::mem_fun(this, &ControlPanel::soundToggleClicked));
	forward->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::forwardClicked));
	backward->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::backwardClicked));
	cancel->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::cancelClicked));
	open->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::openButtonClicked));
	backInFile->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::rewindButtonClicked));
	soundAdj->signal_value_changed().connect(sigc::mem_fun(this, &ControlPanel::soundLevelChanged));
	timeProgress->signal_button_press_event().connect(
			sigc::mem_fun(this, &ControlPanel::timeProgressClicked));
	timeProgress->signal_query_tooltip().connect(sigc::mem_fun(this, &ControlPanel::toolTipShow));
	thisOptionsButton->signal_clicked().connect(sigc::mem_fun(this, &ControlPanel::thisOptionsClicked));
	initHashTable(hashTableOfFunction);
}

bool ControlPanel::toolTipShow(int x, int y, bool keyboard_tooltip,
		const Glib::RefPtr<Gtk::Tooltip>& tooltip) {
	toolTipWindow.hide();
	if (duration == -1)
		return false;
	int secTime = (int) (x / (double) timeProgress->get_width() * duration);
	toolTipLabel->set_text(timeToWellText(secTime));
	return true;
}
void ControlPanel::hideLoading(){
	loadProgress->hide();
	time->show();
}
void ControlPanel::showLoading(){
	time->hide();
	loadProgress->show();
}
bool ControlPanel::timeProgressClicked(GdkEventButton* event) {
	if (event->type == GDK_BUTTON_PRESS) {
		if (duration > -1) {
			double pos = (1.0 / duration)
					* (int) ((event->x / (double) timeProgress->get_width()) * duration);
			timeProgress->set_fraction(pos);
			timelineChanged();
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
	time->set_text(getTimeText(position, duration));
	timeline_changed_signal = false;
	timeline_changed_signal = true;
}
void ControlPanel::setPosition(int seconds) {
	position = seconds;
	if(position > duration)
		position = duration;
	if (duration >= 0) {
		time->set_text(getTimeText(position, duration));
		if (aktualizeTextSignal) {
			timeline_changed_signal = false;
			timeProgress->set_fraction(position / (double) duration);
			timeline_changed_signal = true;
		}
	}
}
void ControlPanel::setAudioLevel(double level) {
	if(level > 100)
		level = 100;
	if(level < 0)
		level = 0;
	sound_changed_signal = false;
	soundAdj->set_value(level);
	sound_changed_signal = true;
}
double ControlPanel::getAudioLevel() {
	return soundAdj->get_value();
}
int ControlPanel::getTime() {
	return timeProgress->get_fraction() * duration;
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
void ControlPanel::setBridgePointer(Bridge* windowBridge){
	this->windowBridge = windowBridge;
}
//---------------------private functions---------------------------//
Glib::ustring ControlPanel::getTimeText(int position, int duration) {
	if (position < 0 || duration < 0) {
		return ("--:-- / --:--");
	}
	Glib::ustring time = timeToWellText(position) + "/" + timeToWellText(duration);
	return time;
}
Glib::ustring ControlPanel::timeToWellText(int time) {
	Glib::ustring ttmm = "";
	int sec = time % 60;
	int min = (time - sec) % 3600;
	int hod = (time - min - sec);
	min /= 60;
	hod /= 3600;
	if (hod > 0)
		ttmm += Glib::ustring::format(hod) + ":";
	if (min < 10)
		ttmm += "0";
	ttmm += Glib::ustring::format(min) + ":";
	if (sec < 10)
		ttmm += "0";
	ttmm += Glib::ustring::format(sec);
	return ttmm;
}
void ControlPanel::soundLevelChanged() {
	if (playerSignals != 0 && sound_changed_signal)
		playerSignals->changeSoundLevel();
}
void ControlPanel::timelineChanged() {
	if (timeline_changed_signal) {
		aktualizeTextSignal = false;
		setPosition(getTime());
		aktualizeTextSignal = true;
		if (playerSignals != 0)
			playerSignals->changeTimeLine();
	}
}
void ControlPanel::openButtonClicked() {
	if (windowBridge != 0)
		windowBridge->clickOpenButton();
}
void ControlPanel::forwardClicked() {
	if (playerSignals != 0)
		playerSignals->clickForward();
}
void ControlPanel::backwardClicked() {
	if (playerSignals != 0)
		playerSignals->clickBackward();
}
void ControlPanel::cancelClicked() {
	if (playerSignals != 0)
		playerSignals->clickCancel();
}
void ControlPanel::thisOptionsClicked() {
	if (windowBridge != 0)
		windowBridge->clickThisOptionsButton();
}
void ControlPanel::rewindButtonClicked() {
	if (playerSignals != 0)
		playerSignals->clickRewind();
}
void ControlPanel::playToggleClicked() {
	if (playStop->get_active() == true)
		playStop->set_image(pauseImage);
	else
		playStop->set_image(playImage);

	if (playerSignals != 0 && playStopSignal) {
		if (playStop->get_active() == true)
			playerSignals->clickPlay();
		else
			playerSignals->clickPause();
	}
}
void ControlPanel::playStopSoftPressed(){
	playStop->set_active(!playStop->get_active());
}
void ControlPanel::muteUnmuteSoftPressed(){
	soundMute->set_active(!soundMute->get_active());
}
void ControlPanel::soundToggleClicked() {
	if (playerSignals != 0) {
		if (soundMute->get_active() == true) {
			sound->set_sensitive(false);
			soundMute->set_image(muteImage);
			playerSignals->clickMute();
		} else {
			sound->set_sensitive(true);
			soundMute->set_image(soundImage);
			playerSignals->clickSound();
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
void ControlPanel::call(IndigoPlayerEnum::Command command){
	if(hashTableOfFunction.find(command) != hashTableOfFunction.end()){
		OFP func = hashTableOfFunction[command];
		(this->*func)();
	}
}
std::list<IndigoPlayerEnum::Command> ControlPanel::getCommandList(){
	std::list<IndigoPlayerEnum::Command> list;
	std::map <IndigoPlayerEnum::Command, OFP>::iterator it;
	for(it = hashTableOfFunction.begin(); it != hashTableOfFunction.end(); it++){
		list.push_back(it->first);
	}
	return list;
}
void ControlPanel::initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table){
	table[IndigoPlayerEnum::PLAYSTOPBUT] = &ControlPanel::playStopSoftPressed;
	table[IndigoPlayerEnum::MUTEUNMUTE] = &ControlPanel::muteUnmuteSoftPressed;
}
