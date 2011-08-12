/*
 * PlaylistGraphic.cpp
 *
 *  Created on: 5.8.2011
 *      Author: xgeier
 */

#include "PlaylistGraphic.h"

#include <iostream>

PlaylistGraphic::PlaylistGraphic(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	numberOfRows = 0;
	isSetCurrentRow = false;
	deleteAktualB = false;
	crFile = NULL;
	refGlade->get_widget("RandomToButtonPlaylist", random);
	refGlade->get_widget("RepeatToButtonPlaylist", repeat);
	refGlade->get_widget("CloseToButtonPlaylist", close);
	refGlade->get_widget("RemoveAllPlaylist", removeAll);
	refGlade->get_widget("RemoveSelectedPlaylist", removeSelected);
	refGlade->get_widget("PlaylistBoard", playlistBoard);
	refGlade->get_widget("SearchEntry", searchEntry);

	playlistBoardModel = Gtk::ListStore::create(m_Columns);
	playlistBoard->set_model(playlistBoardModel);
	playlistBoard->append_column("Go", m_Columns.image);
	playlistBoard->append_column("File name", m_Columns.fileName);
	playlistBoard->set_rules_hint(true);
	refTreeSelection = playlistBoard->get_selection();
	refTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);

	removeAll->signal_clicked().connect(sigc::mem_fun(this, &PlaylistGraphic::removeAllClicked));
	removeSelected->signal_clicked().connect(sigc::mem_fun(this, &PlaylistGraphic::removeSelectedClicked));
	playlistBoard->signal_row_activated().connect(sigc::mem_fun(this, &PlaylistGraphic::doubleClickOnBoard));
	playlistBoard->signal_key_press_event().connect(sigc::mem_fun(this, &PlaylistGraphic::on_button_clicked));
	playlistBoard->set_search_entry(*searchEntry);

	arrowImage = Gdk::Pixbuf::create_from_file("arrow2.png");
	clearImage = Gdk::Pixbuf::create_from_file("arrowc.png");

//	crRow = *playlistBoardModel->children().begin();
}

PlaylistGraphic::~PlaylistGraphic() {

}
bool PlaylistGraphic::isRandom(){
	return random->get_active();
}
bool PlaylistGraphic::isRepeat(){
	return repeat->get_active();
}
bool PlaylistGraphic::isClose(){
	return close->get_active();
}
void PlaylistGraphic::setListener(PlayerSignals* sig) {
	signal = sig;
}
void PlaylistGraphic::removeAllClicked() {
	isSetCurrentRow = false;
	numberOfRows = 0;
	playlistBoardModel->clear();
}
void PlaylistGraphic::removeSelectedClicked() {
	std::vector<Gtk::TreeModel::Path> paths = refTreeSelection->get_selected_rows();
	Gtk::TreeModel::iterator it;
	for (unsigned int i = 0; i < paths.size(); i++) {
		it = playlistBoardModel->get_iter(paths[i]);
		if (it) {
			if(*it == crRow){
				isSetCurrentRow = false;
			}
			if(*it == crRow)
				deleteAktualB = true;
			delete (*it)[m_Columns.file];
			playlistBoardModel->erase(it);
			numberOfRows--;
		}
	}
}
void PlaylistGraphic::doubleClickOnBoard(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*) {
	Gtk::TreeModel::Row row = *playlistBoardModel->get_iter(path);
	if (row) {
		if(isSetCurrentRow)
			crRow[m_Columns.image] = clearImage;
		crRow = row;
		crRow[m_Columns.image] = arrowImage;
		isSetCurrentRow = true;
	}
	signal->clickPlaylistBoard();
}
bool PlaylistGraphic::on_button_clicked(GdkEventKey* evt) {
	if (evt->type == GDK_KEY_PRESS)
		if (evt->keyval == 65535) {
			this->removeSelectedClicked();
		}
	return true;
}
void PlaylistGraphic::addLine(IndigoFile *file, bool save) {
	numberOfRows++;
	boardRow = *(playlistBoardModel->append());
	boardRow[m_Columns.fileName] = file->getName();
	boardRow[m_Columns.image] = clearImage;
	boardRow[m_Columns.file] = file;
	if(save)
		lastAddSave = boardRow;
}
bool PlaylistGraphic::getNext() {
	std::cout<<"getNext()"<<std::endl;
	if (!isSetCurrentRow && numberOfRows > 0) {
		if (playlistBoardModel->children().begin()) {
			crRow = *playlistBoardModel->children().begin();
			crRow[m_Columns.image] = arrowImage;
			isSetCurrentRow= true;
		}
	} else {
		if (numberOfRows > 0) {
			if (++crRow != *playlistBoardModel->children().end()) {
				crRow--;
				crRow[m_Columns.image] = clearImage;
				crRow++;
				crRow[m_Columns.image] = arrowImage;
			} else {
				crRow--;
				return false;
			}
		}
	}
	return true;
}
void PlaylistGraphic::getBack() {
	if(!isSetCurrentRow && numberOfRows > 0){
		if (playlistBoardModel->children().begin()){
			crRow = *playlistBoardModel->children().end();
			--crRow;
			crRow[m_Columns.image] = arrowImage;
			isSetCurrentRow= true;
		}
	}else{
		if(numberOfRows > 0){
			if (crRow != *playlistBoardModel->children().begin()) {
				crRow[m_Columns.image] = clearImage;
				crRow--;
				crRow[m_Columns.image] = arrowImage;
			}
		}
	}
}
void PlaylistGraphic::getRandom() {
	if(numberOfRows > 0){
		Glib::Rand moj;
		int cislo = moj.get_int_range(0, numberOfRows);
		if(isSetCurrentRow)
			crRow[m_Columns.image] = clearImage;
		crRow = *playlistBoardModel->children()[cislo];
		crRow[m_Columns.image] = arrowImage;
	}
}
void PlaylistGraphic::jumpToLastSave(){
	if(*lastAddSave){
		if(isSetCurrentRow)
			crRow[m_Columns.image] = clearImage;
		crRow = lastAddSave;
		crRow[m_Columns.image] = arrowImage;
		isSetCurrentRow = true;
	}
}
IndigoFile* PlaylistGraphic::copyFile(Gtk::TreeModel::Row &row){
	if(*row){
		IndigoFile *f = new IndigoFile();
		*f = *row[m_Columns.file];
		return f;
	}
	return NULL;
}
IndigoFile* PlaylistGraphic::getFile(){
	if(*crRow){
		if(crFile)
			delete crFile;
		crFile = copyFile(crRow);
	}
	deleteAktualB = false;
	return crFile;
}
bool PlaylistGraphic::isEmpty(){
	return numberOfRows == 0;
}
bool PlaylistGraphic::deleteAktual(){
	return deleteAktualB;
}
