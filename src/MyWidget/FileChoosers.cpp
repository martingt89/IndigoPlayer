/*
 * FileChoosers.cpp
 *
 *  Created on: 22.8.2011
 *      Author: xgeier
 */

#include "FileChoosers.h"

FileChoosers::FileChoosers() {
	fileOpen = new Gtk::FileChooserDialog("", Gtk::FILE_CHOOSER_ACTION_OPEN);
	fileOpen->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileOpen->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
//	fileOpen->
	clear();
}

FileChoosers::~FileChoosers() {
	delete fileOpen;
}

Glib::ustring FileChoosers::getSubtitleFile() {
	fileOpen->set_title("Select subtitle file");
	int result = fileOpen->run();
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		return fileOpen->get_filename();
	}
	case (Gtk::RESPONSE_CANCEL): {
		return "";
	}
	default: {
		return "";
	}
	}
}
Glib::ustring FileChoosers::getSoundFile() {
	fileOpen->set_title("Select sound file");
	int result = fileOpen->run();
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		return fileOpen->get_filename();
	}
	case (Gtk::RESPONSE_CANCEL): {
		return "";
	}
	default: {
		return "";
	}
	}
}
Glib::ustring FileChoosers::showFileChooser(Glib::ustring title) {
	fileOpen->set_title(title);
	int result = fileOpen->run();
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		return fileOpen->get_filename();
	}
	case (Gtk::RESPONSE_CANCEL): {
		return "";
	}
	default: {
		return "";
	}
	}
}
void FileChoosers::clear(){
	Glib::ustring path = "";
	path = Glib::get_user_special_dir(G_USER_DIRECTORY_VIDEOS);
	if(path.size()==0){
		path = Glib::get_home_dir ();
	}
	if(path.size() != 0){
		fileOpen->set_current_folder(path);
	}
}
void FileChoosers::hide(){
	fileOpen->hide();
}
