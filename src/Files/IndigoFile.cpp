/*
 * IndigoFile.cpp
 *
 *  Created on: 2.8.2011
 *      Author: xgeier
 */

#include "IndigoFile.h"

IndigoFile::IndigoFile(Glib::ustring path, IndigoFileType::FileType type) {
	init();
	filePath = path;
	this->type = type;

}
IndigoFile::IndigoFile() {
	init();
}
IndigoFile::~IndigoFile() {
}
void IndigoFile::init(){
	filePath = "";
	menu = false;
	subtitleFile = "";
	subtitleFPS = -1;
	subtitleDelayms = 0;
	soundDelayms = 0;
	type = IndigoFileType::UNKNOWN;
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
//::::::::::::::::::::::::::::::::::::::::::::::
void IndigoFile::setMenu(bool menu){
this->menu = menu;
}
void IndigoFile::setSoundFile(Glib::ustring sound){
	soundFile = sound;
}
void IndigoFile::setSubtitleFile(Glib::ustring subtitle){
	subtitleFile = subtitle;
}
void IndigoFile::setSubtitleFPS(double fps){
	subtitleFPS = fps;
}
void IndigoFile::setSubtitleDelayms(int delay){
	subtitleDelayms = delay;
}
void IndigoFile::setSoundDelayms(int delay){
	soundDelayms = delay;
}
