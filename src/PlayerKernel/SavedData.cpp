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
void SavedData::setSubtitle(Glib::ustring path){
	subPath = path;
}
Glib::ustring  SavedData::getSubPath(){
	return subPath;
}
