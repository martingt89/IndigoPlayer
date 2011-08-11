/*
 * Playlist.cpp
 *
 *  Created on: 28.6.2011
 *      Author: xgeier
 */

#include "Playlist.h"

#include <iostream>

Playlist::Playlist(PlaylistGraphic* graphic) {
	file = NULL;
	this->graphic = graphic;
}

Playlist::~Playlist() {

}

void Playlist::setListener(PlayerSignals* sig){
	graphic->setListener(sig);
}

void Playlist::addFiles(std::list<IndigoFile*> files){
	std::list<IndigoFile*>::iterator it;
	it = files.begin();
	if(it != files.end()){
		graphic->addLine(*it, true);
	}
	for(it++; it != files.end(); it++){
		graphic->addLine(*it, false);
	}
}

IndigoFile* Playlist::getFile(){
	std::cout<<"getFile()"<<std::endl;
	if(!graphic->deleteAktual() && file)
		return file;
	this->goNextFile();
		return file;
}

void Playlist::goNextFile(){
	if(graphic->isRandom()){
		graphic->getRandom();
	}else{
		graphic->getNext();
	}
	file = graphic->getFile();
}

void Playlist::goPrevioseFile(){
	graphic->getBack();
	file = graphic->getFile();
}

void Playlist::jumpToLastAdd(){
	graphic->jumpToLastSave();
	file = graphic->getFile();
}

bool Playlist::isEmpty(){
	return graphic->isEmpty();
}
void Playlist::aktualizeFile(){
	file = graphic->getFile();
}
