/*
 * GraphicData.cpp
 *
 *  Created on: 2.9.2011
 *      Author: xgeier
 */

#include "GraphicData.h"
#include <iostream>
GraphicData::GraphicData() {
	start = false;
	end = false;
	aktualTime = 0;
	duration = 0;
	width = 0;
	height = 0;
	//
	wasStart = false;
	wasEnd = false;
	wasAktualTime = false;
	wasDuration = false;
	wasResolution = false;
	wasSubtitle = false;
	wasAudio = false;
	wasAktualAudio = false;
	wasAktualSubtitle = false;
}

void GraphicData::setStart(bool start){
	wasStart = true;
	this->start= start;
}
void GraphicData::setEnd(bool end){
	wasEnd = true;
	this->end = end;
}
void GraphicData::setAktualTime(int time){
	wasAktualTime = true;
	aktualTime = time;
}
void GraphicData::setLength(int length){
	wasDuration = true;
	duration = length;
}
void GraphicData::setResolution(int width, int height){
	wasResolution = true;
	this->width = width;
	this->height = height;
}
void GraphicData::setSubtitleList(std::list<Glib::ustring> subtitle){
	wasSubtitle = true;
	this->subtitle = subtitle;
}
void GraphicData::setAudioList(std::list<Glib::ustring> audio){
	wasAudio = true;
	this->audio = audio;
}
void GraphicData::setAktualAudio(Glib::ustring audioStream){
	wasAktualAudio = true;
	aktualAudio = audioStream;
}
void GraphicData::setAktualSubtitle(Glib::ustring subtitleStream){
	wasAktualSubtitle = true;
	aktualSubtitle = subtitleStream;
}
bool GraphicData::getStart(){
	return start;
}
bool GraphicData::getEnd(){
	return end;
}
int GraphicData::getAktualTime(){
	return aktualTime;
}
int GraphicData::getLenght(){
	return duration;
}
void GraphicData::getResolution(int *width, int* height){
	*width = this->width;
	*height = this->height;
}
std::list<Glib::ustring> GraphicData::getSubtitleList(){
	return subtitle;
}
std::list<Glib::ustring> GraphicData::getAudioList(){
	return audio;
}
Glib::ustring GraphicData::getAktualAudio(){
	return aktualAudio;
}
Glib::ustring GraphicData::getAktualSubtitle(){
	return aktualSubtitle;
}
//
bool GraphicData::isStart(){
	return wasStart;
}
bool GraphicData::isEnd(){
	return wasEnd;
}
bool GraphicData::isAktualTime(){
	return wasAktualTime;
}
bool GraphicData::isLenght(){
	return wasDuration;
}
bool GraphicData::isResolution(){
	return wasResolution;
}
bool GraphicData::isSubtitle(){
	return wasSubtitle;
}
bool GraphicData::isAudio(){
	return wasAudio;
}
bool GraphicData::isAktualAudio(){
	return wasAktualAudio;
}
bool GraphicData::isAktualSubtitle(){
	return wasAktualSubtitle;
}
