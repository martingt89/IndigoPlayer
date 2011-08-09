/*
 * BasePlayerWindow.cpp
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 *
 * Nacitanie zakladneho okna, zakladna logika grafiky
 * pri aktivacii prostredia, vola metody interfejsu
 */

#include "BasePlayerWindow.h"

#include <iostream>

BasePlayerWindow::BasePlayerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
		Gtk::Window(cobject), m_refGlade(refGlade), timelineAdj(0.0, 0.0, 0.0), soundAdj(0, 0, 100),
		playerSignals(0) {

	timeline_changed_signal = true;
	sound_changed_signal = true;
	playStopSignal = true;
	isFull = false;

	m_refGlade->get_widget("ForwardButtonBase", forward);
	m_refGlade->get_widget("BackwardButtonBase", backward);
	m_refGlade->get_widget("PlayStopTButtonBase", playStop);
	m_refGlade->get_widget("CanceButtonBase", cancel);
	m_refGlade->get_widget("FullscreenButtonBase", fullScreen);
	m_refGlade->get_widget("ThisOptionsButtonBase", thisOptions);
	m_refGlade->get_widget("MuteTButtonBase", soundMute);
	m_refGlade->get_widget("BackInFileButtonBase", backInFile);
	m_refGlade->get_widget("TimeLineHScaleBase", timeline);
	m_refGlade->get_widget("SoundHScaleBase", sound);
	m_refGlade->get_widget("TimeLabelBase", time);
	m_refGlade->get_widget("PanelVBoxBase", panel);
	m_refGlade->get_widget("CapitalPanelVBoxBase", capitalPanel);
	m_refGlade->get_widget("SeparatorHSeparatorBase", separator);
	m_refGlade->get_widget("VideoToggleBase", video);
	m_refGlade->get_widget("PlaylistToggleBase", playlist);
	m_refGlade->get_widget("OpenButtonBase", open);
	m_refGlade->get_widget("PlayerNotebookBase", notebook);
	m_refGlade->get_widget("PopupWindow", popupWindow);
	m_refGlade->get_widget("CapitalPopupVBox", capitalPopupVBox);

	timeline->set_adjustment(timelineAdj);
	sound->set_adjustment(soundAdj);
	soundAdj.set_value(100);
	playStop->signal_toggled().connect(sigc::mem_fun(this, &BasePlayerWindow::on_toggledPlay_clicked));
	soundMute->signal_toggled().connect(sigc::mem_fun(this, &BasePlayerWindow::on_toggledSound_clicked));
	forward->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::forward_clicked));
	backward->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::backward_clicked));
	cancel->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::cancel_clicked));
	fullScreen->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::fullScreen_clicked));
	thisOptions->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::thisOptions_clicked));
	open->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::open_clicked));
	backInFile->signal_clicked().connect(sigc::mem_fun(this, &BasePlayerWindow::backInFile_clicked));
	timelineAdj.signal_value_changed().connect(sigc::mem_fun(this, &BasePlayerWindow::timeline_changed));
	soundAdj.signal_value_changed().connect(sigc::mem_fun(this, &BasePlayerWindow::sound_changed));
	video->signal_toggled().connect(sigc::mem_fun(this, &BasePlayerWindow::videoPlaylistOpen));
	playlist->signal_toggled().connect(sigc::mem_fun(this, &BasePlayerWindow::videoPlaylistOpen));
	//
	capitalPanel->pack_end(*panel, false, false, 0);
	std::list<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry("text/uri-list"));
	this->drag_dest_set(listTargets);
	this->signal_drag_data_received().connect(sigc::mem_fun(*this, &BasePlayerWindow::on_drop_files));
	//
	this->clearTime();
	this->setWindowTitle("");
	notebook->set_current_page(0);
	video->set_active(true);
	stopVPO = false;
	//----------------------------------
	signal_key_press_event().connect(sigc::mem_fun(this, &BasePlayerWindow::on_button_clicked), false);
	//std::cout<<panel->get_height()<<std::endl;
}
bool BasePlayerWindow::on_button_clicked(GdkEventKey* evt){
	std::cout<<evt->keyval<<std::endl;
	if(evt->type == GDK_KEY_PRESS)
		if (evt->keyval == 65535){
			std::cout<<"postav sa na hlavu"<<std::endl;
		}
	return false;
}
void BasePlayerWindow::setWindowTitle(Glib::ustring title) {
	Glib::ustring name = Glib::ustring(NAME) + " " + Glib::ustring::format(VERSION) + " " + title;
	this->set_title(name);
}
void BasePlayerWindow::clearTime() {
	duration = -1;
	position = -1;
	time->set_text(getTimeText(position, duration));
	timelineAdj.set_upper(0);
	timelineAdj.set_value(0);
}
void BasePlayerWindow::setDuration(int seconds) {
	duration = seconds;
	position = 0;
	time->set_text(getTimeText(position, duration)); //TODO //prepisat na multi threading
	timeline_changed_signal = false;
	timelineAdj.set_upper(duration);
	timelineAdj.set_value(position);
	timeline_changed_signal = true;
}
void BasePlayerWindow::setPosition(int seconds) {
	position = seconds;
	if (duration >= 0) {
		time->set_text(getTimeText(position, duration)); //TODO //prepisat na multi threading
		timeline_changed_signal = false;
		timelineAdj.set_upper(duration);
		timelineAdj.set_value(position);
		timeline_changed_signal = true;
	}
}
void BasePlayerWindow::setAudioLevel(double level) {
	sound_changed_signal = false;
	soundAdj.set_value(level); //TODO //prepisat na multi threading
	sound_changed_signal = true;
}

double BasePlayerWindow::getAudioLevel() {
	return soundAdj.get_value(); //TODO //prepisat na multi threading
}
void BasePlayerWindow::openFullscreen() {
	isFull = true;
	capitalPanel->remove(*panel);
	separator->set_visible(false);
	this->fullscreen();
	capitalPopupVBox->pack_end(*panel, true, true, 0);
	popupWindow->resize(this->get_screen()->get_width(), 64);
	//panel->get_height()
	popupWindow->move(0, this->get_screen()->get_height() - 64);
	popupWindow->set_visible(true);
}
void BasePlayerWindow::closeFullscreen() {
	isFull = false;
	capitalPopupVBox->remove(*panel);
	popupWindow->set_visible(false);
	capitalPanel->pack_end(*panel, false, false, 0);
	separator->set_visible(true);
	this->unfullscreen();
}
void BasePlayerWindow::popPlayButton() {
	playStopSignal = false;
	playStop->set_active(false);
	playStopSignal = true;
}
bool BasePlayerWindow::isFullscreen(){
	return isFull;
}
//---------------------private functions---------------------------//
Glib::ustring BasePlayerWindow::getTimeText(int position, int duration) {
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
void BasePlayerWindow::on_drop_files(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
		const Gtk::SelectionData& selection_data, guint info, guint time) {

	const int length = selection_data.get_length();
	if ((length >= 0) && (selection_data.get_format() == 8)) {
		std::vector<Glib::ustring> file_list;
		file_list = selection_data.get_uris();
//		if(file_list.size() == 0){
//			test_for_subtitle()
//		}
		std::list<Glib::ustring>::iterator listIter2;
		std::list<IndigoFile*> uris;
		FileUtilities fu;
		for (unsigned int i = 0; i < file_list.size(); i++) {
			std::list<Glib::ustring> ma = fu.fileToPlaylist(file_list[i]);
			for(listIter2 = ma.begin(); listIter2 != ma.end(); listIter2++)
				uris.push_back(new IndigoFile(*listIter2, true));
		}
		if (file_list.size() > 0 && playerSignals != 0)
			playerSignals->addFiles(uris, notebook->get_current_page() != 1);
	}

	context->drag_finish(false, false, time);
}
//---------------------signal functions---------------------------//
void BasePlayerWindow::videoPlaylistOpen() {
	if (stopVPO)
		return;
	if (notebook->get_current_page() == 0 && video->get_active() == false) {
		stopVPO = true;
		video->set_active(true);
		stopVPO = false;
		return;
	}
	if (notebook->get_current_page() == 1 && playlist->get_active() == false) {
		stopVPO = true;
		playlist->set_active(true);
		stopVPO = false;
		return;
	}
	if (notebook->get_current_page() != 0 && video->get_active()) {
		stopVPO = true;
		playlist->set_active(false);
		notebook->set_current_page(0);
		stopVPO = false;
	}
	if (notebook->get_current_page() != 1 && playlist->get_active()) {
		stopVPO = true;
		video->set_active(false);
		notebook->set_current_page(1);
		stopVPO = false;
	}
}
void BasePlayerWindow::sound_changed() {
	if (playerSignals != 0 && sound_changed_signal)
		playerSignals->changeSoundLevel();
}
void BasePlayerWindow::timeline_changed() {
	setPosition(timelineAdj.get_value());
	if (playerSignals != 0 && timeline_changed_signal)
		playerSignals->changeTimeLine();
}
void BasePlayerWindow::open_clicked() {
	if (playerSignals != 0)
		playerSignals->clickOpen();
}
void BasePlayerWindow::forward_clicked() {
	if (playerSignals != 0)
		playerSignals->clickForward();
}
void BasePlayerWindow::backward_clicked() {
	if (playerSignals != 0)
		playerSignals->clickBackward();
}
void BasePlayerWindow::cancel_clicked() {
	if (playerSignals != 0)
		playerSignals->clickCancel();
}
void BasePlayerWindow::fullScreen_clicked() {
	if (playerSignals != 0)
		playerSignals->clickFullscreen();
}
void BasePlayerWindow::thisOptions_clicked() {
	if (playerSignals != 0)
		playerSignals->clickThisOptions();
}
void BasePlayerWindow::backInFile_clicked() {
	if (playerSignals != 0)
		playerSignals->clickRewind();
}
void BasePlayerWindow::on_toggledPlay_clicked() {
	if (playerSignals != 0 && playStopSignal) {
		if (playStop->get_active() == true)
			playerSignals->clickPlay();
		else
			playerSignals->clickPause();
	}
}
void BasePlayerWindow::on_toggledSound_clicked() {
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
void BasePlayerWindow::setSignalListener(PlayerSignals *ps) {
	playerSignals = ps;
}

BasePlayerWindow::~BasePlayerWindow() {
	delete forward;
	delete backward;
	delete cancel;
	delete fullScreen;
	delete kill;
	delete backInFile;
	delete playlist;
	delete thisOptions;
	delete open;
	delete playStop;
	delete soundMute;
	delete timeline;
	delete sound;
	delete time;
	delete panel;
	delete separator;
}
