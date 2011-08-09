/*
 * IndigoFile.cpp
 *
 *  Created on: 2.8.2011
 *      Author: xgeier
 */

#include "IndigoFile.h"

IndigoFile::IndigoFile(Glib::ustring path, bool trust) {
	filePath = path;
//	play = false;
//this->menu = menu;
//if(Glib::file_test(path, Glib::FILE_TEST_EXISTS)){
//	filePath = path;
//}else{
//	static Glib::RefPtr< Gio::File > file = Gio::File::create_for_uri (path);
//	if(file->get_path().length() != 0){
//		filePath = file->get_path();
//	}else
//		if(file->get_uri().length() != 0){
//			filePath = file->get_uri();
//		}else{
//			filePath = path;
//		}
//	}
}
IndigoFile::IndigoFile(IndigoFile* file){
	//name =  file->getName();
	filePath = file->getFilePath();
	menu =  file->getMenu();
	soundFile = file->getSoundFile();
	subtitleFile = file->getSubtitleFile();
//	bool getPlay;
	subtitleFPS = file->getSubtitleFPS();
	subtitleDelayms = file->getSubtitleDelayms();
	soundDelayms = file->getSoundDelayms();
}
IndigoFile::~IndigoFile() {
	// TODO Auto-generated destructor stub
}

Glib::ustring IndigoFile::getName(){
	return filePath;
}
Glib::ustring IndigoFile::getFilePath(){
	return filePath;
}
bool IndigoFile::getMenu(){
	return menu;
}
Glib::ustring IndigoFile::getSoundFile(){
	return soundFile;
}
Glib::ustring IndigoFile::getSubtitleFile(){
	return subtitleFile;
}
double IndigoFile::getSubtitleFPS(){
	return subtitleFPS;
}
int IndigoFile::getSubtitleDelayms(){
	return subtitleDelayms;
}
int IndigoFile::getSoundDelayms(){
	return soundDelayms;
}
