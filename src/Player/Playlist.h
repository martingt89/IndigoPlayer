/*
 * Playlist.h
 *
 *  Created on: 28.6.2011
 *      Author: xgeier
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <glibmm.h>
#include <gtkmm.h>

class Playlist {
public:
	Playlist();
	virtual ~Playlist();
	void addFile(Glib::ustring path);
	void removAll();
	//---------------------
	Glib::ustring getNext();
	Glib::ustring getPrev();
	//---------------------
	void setRandom(bool random);
	void setAround(bool around);
	void setClose(bool close);
	//---------------------
	void show(bool visible);
	void setPlaylistWindow();
private:
	Gtk::Window playlist;
	Gtk::ToggleButton random;
	Gtk::ToggleButton repeat;
	Gtk::ToggleButton close;
};

#endif /* PLAYLIST_H_ */
