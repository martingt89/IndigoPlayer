/*
 * SavedFileInfo.cpp
 *
 *  Created on: 1.9.2011
 *      Author: xgeier
 */

#include "SavedFileInfo.h"

SavedFileInfo::SavedFileInfo() {
	clear();
}
void SavedFileInfo::setAktulaTime(int time){
	aktualTime = time;
}
void SavedFileInfo::pause(){
	pp = !pp;
}
void SavedFileInfo::setCrop(int up, int down, int left, int right){
	this->cropUP = up;
	this->cropDown = down;
	this->cropLeft = left;
	this->cropRight = right;
}
void SavedFileInfo::setSubtitlePosition(double pos){
	this->subtitlePosition = pos;
}
void SavedFileInfo::setSoundPosition(double pos){
	this->soundPosition = pos;
}
void SavedFileInfo::setPlaySpeed(double speed){
	this->playSpeed = speed;
}
void SavedFileInfo::setRotate(int rotate){
	this->rotate = rotate;
}
void SavedFileInfo::setResolution(int width, int height){
	this->width = width;
	this->height = height;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SavedFileInfo::setSubtitlePath(Glib::ustring path){
	subPath = path;
	subID = -1;
}
void SavedFileInfo::setSubtitleID(int id){
	subPath = "";
	subID = id;
}
void SavedFileInfo::setAudioPath(Glib::ustring path){
	audioPath = path;
	audioID = -1;
}
void SavedFileInfo::setAudioID(int id){
	audioPath = "";
	audioID = id;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SavedFileInfo::setNumberOfChapters(int number){
	numberChapters = number;
}
void SavedFileInfo::setAktualChapter(int chapter){
	aktualChapter = chapter;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SavedFileInfo::setHue(double hue){this->hue = hue;}
void SavedFileInfo::setGamma(double gama){gamma = gama;}
void SavedFileInfo::setContrast(double con){contrast = con;}
void SavedFileInfo::setSaturation(double satur){saturation = satur;}
void SavedFileInfo::setBrightness(double bright){brightness = bright;}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
bool SavedFileInfo::getPause(){
	return pp;
}
int SavedFileInfo::getAktualTime(){
	return aktualTime;
}
void SavedFileInfo::getCrop(int *up, int *down, int *left, int *right){
	*up = cropUP;
	*down = cropDown;
	*left = cropLeft;
	*right = cropRight;
}
double SavedFileInfo::getSubtitlePosition(){
	return subtitlePosition;
}
double SavedFileInfo::getSoundPosition(){
	return soundPosition;
}
double SavedFileInfo::getPlaySpeed(){
	return playSpeed;
}
int SavedFileInfo::getRotate(){
	return rotate;
}
void SavedFileInfo::getResolution(int *width, int *height){
	*width = this->width;
	*height = this->height;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int SavedFileInfo::getSubID(){
	return subID;
}
Glib::ustring SavedFileInfo::getSubPath(){
	return subPath;
}
int SavedFileInfo::getAudioID(){
	return audioID;
}
Glib::ustring SavedFileInfo::getAudioPath(){
	return audioPath;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int SavedFileInfo::getNumberOfChapter(){
	return numberChapters;
}
int SavedFileInfo::getAktualChapter(){
	return aktualChapter;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SavedFileInfo::getCollors(double *brig, double *satur, double *cont, double *gamma, double *hue){
	*brig = brightness;
	*satur = saturation;
	*cont = contrast;
	*gamma = this->gamma;
	*hue = this->hue;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void SavedFileInfo::clear(){
	pp = false;
	width = -1;
	height = -1;
	//==================
	aktualTime = 0;
	subtitlePosition = 0;
	soundPosition = 0;
	//==================
	cropUP = 0;
	cropDown = 0;
	cropLeft = 0;
	cropRight = 0;
	//==================
	playSpeed = 1;
	rotate = 0;
	//==================
	subPath = "";
	audioPath = "";
	subID = -1;
	audioID = -1;
	//==================
	numberChapters = 0;
	aktualChapter = 0;
	//==================
	brightness = 0;
	saturation = 0;
	contrast = 0;
	gamma= 0;
	hue = 0;
}
