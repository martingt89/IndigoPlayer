/*
 * Playlist.h
 *
 *  Created on: 28.6.2011
 *      Author: xgeier
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <list>
#include <iterator>
#include <glibmm/ustring.h>
#include "../Interfaces/PlayerSignals.h"
#include "../Graphic/PlaylistGraphic.h"

class Playlist {
public:
	Playlist(PlaylistGraphic* graphic);
	virtual ~Playlist();
	//---------------------
	void setListener(PlayerSignals*);
	//---------------------
	void addFiles(std::list<IndigoFile*> files);
	//---------------------
	IndigoFile* getFile();
	void aktualizeFile();
	bool goNextFile();
	void goPrevioseFile();
	void jumpToLastAdd();
	bool isEmpty();
private:
	PlaylistGraphic* graphic;
	IndigoFile* file;
};

#endif /* PLAYLIST_H_ */
