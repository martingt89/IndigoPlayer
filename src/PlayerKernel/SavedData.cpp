/*
 * SavedData.cpp
 *
 *  Created on: 16.8.2011
 *      Author: xgeier
 */

#include "SavedData.h"

SavedData::SavedData() {
	resX = 0;
	resY = 0;
	position = 0;
	subPath = "";
	audioPath = "";
	subID = -1;
	audioID = -1;
}

SavedData::~SavedData() {
	// TODO Auto-generated destructor stub
}

void SavedData::setResolution(int x, int y){
	resX = x;
	resY = y;
}
void SavedData::setPosition(double position){
	this->position = position;
}
int SavedData::getX(){
	return resX;
}
int SavedData::getY(){
	return resY;
}
double SavedData::getPosition(){
	return position;
}
void SavedData::setSubtitlePath(Glib::ustring path){
	subPath = path;
}
void SavedData::setSubtitleID(int id){
	subID = id;
}
void SavedData::setAudioPath(Glib::ustring path){
	audioPath = path;
}
void SavedData::setAudioID(int id){
	audioID = id;
}
//-------------------------------------------------
int SavedData::getSubID(){
	return subID;
}
Glib::ustring SavedData::getSubPath(){
	return subPath;
}
int SavedData::getAudioID(){
	return audioID;
}
Glib::ustring SavedData::getAudioPath(){
	return audioPath;
}
