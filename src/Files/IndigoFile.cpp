/*
 * IndigoFile.cpp
 *
 *  Created on: 2.8.2011
 *      Author: xgeier
 */

#include "IndigoFile.h"

IndigoFile::IndigoFile(Glib::ustring path, IndigoFileType::FileType type) {
	filePath = path;
	this->type = type;
}
IndigoFile::IndigoFile() {

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
IndigoFileType::FileType IndigoFile::getType(){
	return type;
}
