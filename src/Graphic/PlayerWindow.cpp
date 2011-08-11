/*
 * PlayerWindow.cpp
 *
 *  Created on: 9.8.2011
 *      Author: xgeier
 */

#include "PlayerWindow.h"
#include <iostream>

PlayerWindow::PlayerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_refGlade(builder), m_Cursor(Gdk::BLANK_CURSOR) {
	stopVPO = false;
	isHideElements = false;
	once = false;
	hasPanel = true;
	popupHasPanel = false;
	playerSignals = NULL;
	m_refGlade->get_widget("FullscreenToggleBase", fullScreen);
	m_refGlade->get_widget("PanelVBoxBase", panel);
	m_refGlade->get_widget("CapitalPanelVBoxBase", capitalPanel);
	m_refGlade->get_widget("VideoToggleBase", video);
	m_refGlade->get_widget("PlaylistToggleBase", playlist);
	m_refGlade->get_widget("PlayerNotebookBase", vidListNotebook);
	m_refGlade->get_widget("PopupWindow", popupWindow);
	m_refGlade->get_widget("CapitalPopupVBox", capitalPopupVBox);
	m_refGlade->get_widget("PlaylistPanel", playlistPanel);

	capitalPanel->pack_end(*panel, false, false, 0);
	panelHeight = 64;
	std::list<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry("text/uri-list"));
	this->drag_dest_set(listTargets);

	vidListNotebook->set_current_page(0);
	video->set_active(true);
	gdkCapitalWindow = this->get_window();

	this->add_events(Gdk::POINTER_MOTION_MASK);
	fullScreen->signal_toggled().connect(sigc::mem_fun(this, &PlayerWindow::fullScreenClicked));
	video->signal_toggled().connect(sigc::mem_fun(this, &PlayerWindow::videoPlaylistOpen));
	playlist->signal_toggled().connect(sigc::mem_fun(this, &PlayerWindow::videoPlaylistOpen));
	this->signal_drag_data_received().connect(sigc::mem_fun(*this, &PlayerWindow::dropFiles));
	this->signal_key_press_event().connect(sigc::mem_fun(this, &PlayerWindow::keyPress), false);
	this->signal_motion_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::on_my_motion_notify_event));
	popupWindow->signal_leave_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::leavePopup));
	popupWindow->signal_enter_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::enterPopup));
	vidListNotebook->signal_switch_page().connect(sigc::mem_fun(this, &PlayerWindow::switchPage));
	this->signal_hide().connect(sigc::mem_fun(this, &PlayerWindow::quitWindow));
}
PlayerWindow::~PlayerWindow() {
	delete fullScreen;
	delete panel;
	delete capitalPanel;
	delete video;
	delete playlist;
	delete vidListNotebook;
	delete popupWindow;
	delete capitalPopupVBox;
}
void PlayerWindow::quitWindow(){
	if(playerSignals){
		playerSignals->quit();
	}
}
void PlayerWindow::switchPage(GtkNotebookPage* page, guint page_num) {
	if (fullScreen->get_active()) {
		if (page_num == 0) {
			isHideElements = true;
			this->removePanel();
			this->showPopupWindow();
			this->hideElements();
		} else {
			isHideElements = false;
			this->removPopupWindow();
			this->addPanel();
			this->showElements();
		}
	}
}
bool PlayerWindow::leavePopup(GdkEventCrossing* event) {
	noHide = false;
	return true;
}
bool PlayerWindow::enterPopup(GdkEventCrossing* event) {
	noHide = true;
	popupWindow->set_opacity(1);
	return true;
}
bool PlayerWindow::on_my_motion_notify_event(GdkEventMotion* event) {
	if (isHideElements) {
		time.assign_current_time();
		if (!once) {
			once = true;
			myconnection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlayerWindow::on_timeout),
					500);
			popupWindow->set_opacity(1);
			gdkCapitalWindow->set_cursor();
		}
	}
	return true;
}
bool PlayerWindow::on_timeout() {
	aktualtime.assign_current_time();
	aktualtime -= time;
	if (aktualtime.as_double() > 1.3) {
		once = false;
		if (isHideElements) {
			gdkCapitalWindow->set_cursor(m_Cursor);
			if (!noHide)
				popupWindow->set_opacity(0);
		}
		return false;
	}
	return true;
}
void PlayerWindow::setWindowTitle(Glib::ustring title) {
	Glib::ustring name = Glib::ustring(NAME) + " " + Glib::ustring::format(VERSION) + " " + title;
	this->set_title(name);
}
void PlayerWindow::setListener(PlayerSignals* sig) {
	playerSignals = sig;
}
void PlayerWindow::changeFullscreen() {
	fullScreen->set_active(!fullScreen->get_active());
}
void PlayerWindow::removePanel() {
	if (hasPanel) {
		capitalPanel->remove(*panel);
		hasPanel = false;
	}
}
void PlayerWindow::addPanel() {
	if (!hasPanel) {
		capitalPanel->pack_end(*panel, false, false, 0);
		hasPanel = true;
	}
}
void PlayerWindow::showPopupWindow() {
	if (!popupHasPanel) {
		capitalPopupVBox->pack_end(*panel, true, true, 0);
		popupWindow->resize(this->get_screen()->get_width(), panelHeight);
		popupWindow->move(0, this->get_screen()->get_height() - panelHeight);
		popupWindow->set_visible(true);
		popupHasPanel = true;
	}
}
void PlayerWindow::removPopupWindow() {
	if (popupHasPanel) {
		capitalPopupVBox->remove(*panel);
		popupWindow->set_visible(false);
		popupHasPanel = false;
	}
}
void PlayerWindow::hideElements() {
	gdkCapitalWindow->set_cursor(m_Cursor);
	popupWindow->set_opacity(0);
}
void PlayerWindow::showElements() {
	gdkCapitalWindow->set_cursor();
	popupWindow->set_opacity(1);
}
void PlayerWindow::fullScreenClicked() {
	if (fullScreen->get_active()) {
		if (vidListNotebook->get_current_page() == 0) {
			isHideElements = true;
			this->removePanel();
			this->fullscreen();
			this->showPopupWindow();
			this->hideElements();
		} else {
			isHideElements = false;
			this->fullscreen();
		}
	} else {
		isHideElements = false;
		this->showElements();
		this->removPopupWindow();
		this->addPanel();
		this->unfullscreen();
	}
}
void PlayerWindow::videoPlaylistOpen() {
	if (stopVPO)
		return;
	if (vidListNotebook->get_current_page() == 0 && video->get_active() == false) {
		stopVPO = true;
		video->set_active(true);
		stopVPO = false;
		return;
	}
	if (vidListNotebook->get_current_page() == 1 && playlist->get_active() == false) {
		stopVPO = true;
		playlist->set_active(true);
		stopVPO = false;
		return;
	}
	if (vidListNotebook->get_current_page() != 0 && video->get_active()) {
		stopVPO = true;
		playlist->set_active(false);
		vidListNotebook->set_current_page(0);
		playlistPanel->set_visible(false);
		stopVPO = false;
	}
	if (vidListNotebook->get_current_page() != 1 && playlist->get_active()) {
		stopVPO = true;
		video->set_active(false);
		playlistPanel->set_visible(true);
		vidListNotebook->set_current_page(1);
		stopVPO = false;
	}
}
void PlayerWindow::dropFiles(const Glib::RefPtr<Gdk::DragContext>& context, int, int,
		const Gtk::SelectionData& selection_data, guint, guint time) {
	const int length = selection_data.get_length();
	if ((length >= 0) && (selection_data.get_format() == 8)) {
		std::vector<Glib::ustring> file_list;
		file_list = selection_data.get_uris();
//		if(file_list.size() == 0){
//			test_for_subtitle()
//		}
		//	std::cout<<file_list.size()<<std::endl;
		std::list<Glib::ustring>::iterator listIter2;
		std::list<IndigoFile*> uris;
		FileUtilities fu;
		for (unsigned int i = 0; i < file_list.size(); i++) {
			std::list<Glib::ustring> ma = fu.fileToPlaylist(file_list[i]);
			for (listIter2 = ma.begin(); listIter2 != ma.end(); listIter2++) {
				uris.push_back(new IndigoFile(*listIter2, true));
			}
		}
		if (file_list.size() > 0 && playerSignals != 0)
			playerSignals->addFiles(uris, vidListNotebook->get_current_page() != 1);
	}
	context->drag_finish(false, false, time);
}
bool PlayerWindow::keyPress(GdkEventKey* evt) {

	return false;
}
void PlayerWindow::setVideoBoardSize(int x, int y) {
	this->resize(x, y + panelHeight);
}
