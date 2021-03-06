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
	delete graphic;
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
	if(graphic->fileExistInPlaylist()){
		return file;
	}else{
		bool ok;
		if(graphic->isRandom()){
			ok = graphic->getRandom();
		}else{
			ok = graphic->getNext();
		}
		if(ok)
			file = graphic->getFile();
		else{
			file = NULL;
		}
		return file;
	}
}

bool Playlist::goNextFile(){
	bool ok;
	if(graphic->isRandom()){
		ok = graphic->getRandom();
		if(ok)
			file = graphic->getFile();
		else
			file = NULL;
		return ok;
	}else{
		if(!graphic->isLastFile()){
			ok = graphic->getNext();
			if(ok)
				file = graphic->getFile();
			else
				file = NULL;
			return ok;
		}else
			return false;
	}
}

bool Playlist::goPrevioseFile(){
	bool ok;
	ok = graphic->getBack();
	if(ok)
		file = graphic->getFile();
	else
		file = NULL;
	return ok;
}

void Playlist::jumpToLastAdd(){
	graphic->jumpToLastSave();
	file = graphic->getFile();
}

bool Playlist::isEmpty(){
	return graphic->isEmpty();
}
bool Playlist::isLastFile(){
	return graphic->isLastFile();
}
bool Playlist::aktualizeFile(){
	file = graphic->getFile();
	if(file == NULL)
		return false;
	return true;
}
