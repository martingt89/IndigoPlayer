/*
 * PlayerWindow.cpp
 *
 *  Created on: 9.8.2011
 *      Author: xgeier
 */

#include "PlayerWindow.h"
#include <iostream>

#define OPACITYLEVEL 0.7

PlayerWindow::PlayerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_refGlade(builder), m_Cursor(Gdk::BLANK_CURSOR) {
	stopVPO = false;
	isHideElements = false;
	once = false;
	hasPanel = true;
	popupHasPanel = false;
	playerSignals = NULL;
	windowBridge = NULL;
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
	panelWidth = 1024;
	std::list<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry("text/uri-list"));
	this->drag_dest_set(listTargets);

	vidListNotebook->set_current_page(0);
	video->set_active(true);
	gdkCapitalWindow = this->get_window();
	playlistPanel->set_visible(false);
	this->setWindowTitle("");

	popupWindow->set_opacity(OPACITYLEVEL);

	this->add_events(Gdk::POINTER_MOTION_MASK);
	this->signal_check_resize().connect(sigc::mem_fun(this, &PlayerWindow::checkResize));
	fullScreen->signal_toggled().connect(sigc::mem_fun(this, &PlayerWindow::fullScreenClicked));
	video->signal_toggled().connect(sigc::mem_fun(this, &PlayerWindow::videoPlaylistOpen));
	playlist->signal_toggled().connect(sigc::mem_fun(this, &PlayerWindow::videoPlaylistOpen));
	this->signal_drag_data_received().connect(sigc::mem_fun(*this, &PlayerWindow::dropFiles));
	this->signal_key_press_event().connect(sigc::mem_fun(this, &PlayerWindow::keyPress), false);
	this->signal_motion_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::on_my_motion_notify_event));
	//popupWindow->signal_motion_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::on_my_motion_notify_event));
	popupWindow->signal_leave_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::leavePopup));
	popupWindow->signal_enter_notify_event().connect(sigc::mem_fun(this, &PlayerWindow::enterPopup));
	vidListNotebook->signal_switch_page().connect(sigc::mem_fun(this, &PlayerWindow::switchPage));
	this->signal_hide().connect(sigc::mem_fun(this, &PlayerWindow::quitWindow));

    initHashTable(hashTableOfFunction);
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
void PlayerWindow::quitWindow() {
	if (playerSignals) {
		playerSignals->quit();
	}
}
void PlayerWindow::checkResize(){
	if(panelWidth != this->get_width()){
		panelWidth = this->get_width();
		popupWindow->resize(panelWidth, panelHeight);
	}
}
void PlayerWindow::switchPage(GtkNotebookPage* page, guint page_num) {
	if (fullScreen->get_active()) {
		if (page_num == 0) {
			isHideElements = true;
			this->removePanel();
			this->showPopupWindow();
			//this->hideElements();
		} else {
			isHideElements = false;
			this->removPopupWindow();
			this->addPanel();
			//this->showElements();
			gdkCapitalWindow->set_cursor();
		}
	}
}
bool PlayerWindow::leavePopup(GdkEventCrossing* event) {
	if (event->x < 0 || event->y < 0 || event->x > panelWidth || event->y > panelHeight){
		noHide = false;
	}
	return true;
}
bool PlayerWindow::enterPopup(GdkEventCrossing* event) {
	noHide = true;
	popupWindow->show();
	return true;
}
bool PlayerWindow::on_my_motion_notify_event(GdkEventMotion* event) {
	if (isHideElements) {
		time.assign_current_time();
		if (!once) {
			once = true;
			myconnection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlayerWindow::on_timeout),
					500);
			//popupWindow->set_opacity(OPACITYLEVEL);
			popupWindow->show();
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
				//popupWindow->set_opacity(0);
				popupWindow->hide();
		}
		return false;
	}
	return true;
}
void PlayerWindow::setWindowTitle(Glib::ustring title) {
	Glib::ustring name = Glib::ustring(INDIGONAME) + " " + Glib::ustring::format(INDIGOVERSION) + " " + title;
	this->set_title(name);
}
void PlayerWindow::setListener(PlayerSignals* sig) {
	playerSignals = sig;
}
void PlayerWindow::setBridgePointer(Bridge* windowBridge){
	this->windowBridge = windowBridge;
}
void PlayerWindow::changeFullscreen() {
	fullScreen->set_active(!fullScreen->get_active());
}
void PlayerWindow::unFullscreen(){
	fullScreen->set_active(false);
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
	//popupWindow->set_opacity(0);
	popupWindow->hide();
}
void PlayerWindow::showElements() {
	gdkCapitalWindow->set_cursor();
	//popupWindow->set_opacity(OPACITYLEVEL);
	popupWindow->show();
}
void PlayerWindow::setFullscreen(bool full){
	if(fullScreen->get_active() != full)
		changeFullscreen();
}
void PlayerWindow::fullScreenClicked() {
	if (fullScreen->get_active()) {
		if (vidListNotebook->get_current_page() == 0) {
			isHideElements = true;
			once = false;
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
		FileUtilities fu;
		std::list<IndigoFile*> uris;
		uris = fu.stringListToFiles(selection_data.get_uris(), true, 0);
		if (uris.size() == 1 && (*uris.begin())->getType() == IndigoFileType::SUBTITLE) {
			playerSignals->addSubtitle((*uris.begin())->getFilePath());
		}else
		if (uris.size() > 0 && playerSignals != 0)
			playerSignals->addFiles(uris, vidListNotebook->get_current_page() != 1);
	}
	context->drag_finish(false, false, time);
}
bool PlayerWindow::keyPress(GdkEventKey* evt) {
	if (vidListNotebook->get_current_page() == 0) {
		if (windowBridge)
			windowBridge->keyPressed(evt->state, evt->keyval, evt->hardware_keycode);
		return true;
	}
	return false;
}
void PlayerWindow::setVideoBoardSize(int width, int height) {
	this->setFullscreen(false);
	this->unmaximize();
	this->resize(width, height + panelHeight);
}
void PlayerWindow::call(IndigoPlayerEnum::Command command){
	if(hashTableOfFunction.find(command) != hashTableOfFunction.end()){
		OFP func = hashTableOfFunction[command];
		(this->*func)();
	}
}
std::list<IndigoPlayerEnum::Command> PlayerWindow::getCommandList(){
	std::list<IndigoPlayerEnum::Command> list;
	std::map <IndigoPlayerEnum::Command, OFP>::iterator it;
	for(it = hashTableOfFunction.begin(); it != hashTableOfFunction.end(); it++){
		list.push_back(it->first);
	}
	return list;
}
void PlayerWindow::initHashTable(std::map <IndigoPlayerEnum::Command, OFP> &table){
	table[IndigoPlayerEnum::FULLUNFULLSCR] = &PlayerWindow::changeFullscreen;
	table[IndigoPlayerEnum::UNFULLSCR] = &PlayerWindow::unFullscreen;
}
