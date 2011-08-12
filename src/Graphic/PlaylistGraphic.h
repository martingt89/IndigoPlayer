/*
 * PlaylistGraphic.h
 *
 *  Created on: 5.8.2011
 *      Author: xgeier
 */

#ifndef PLAYLISTGRAPHIC_H_
#define PLAYLISTGRAPHIC_H_

#include <vector>
#include <gtkmm/treemodel.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/builder.h>
#include <glibmm/ustring.h>
#include <glibmm/random.h>
#include "../Interfaces/PlayerSignals.h"

class PlaylistGraphic {
private:
	typedef Glib::RefPtr<Gdk::Pixbuf> PixbufPtr;
	class ModelColumns: public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(image);
			add(fileName);
			add(file);
		}
		Gtk::TreeModelColumn<PixbufPtr> image;
		Gtk::TreeModelColumn<Glib::ustring> fileName;
		Gtk::TreeModelColumn<IndigoFile*> file;
	};
public:
	PlaylistGraphic(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~PlaylistGraphic();
	void setListener(PlayerSignals* sig);
	void addLine(IndigoFile *file, bool save);
	bool getNext();
	void getBack();
	void getRandom();
	bool isRandom();
	bool isRepeat();
	bool isClose();
	void jumpToLastSave();
	IndigoFile* getFile();
	bool isEmpty();
	bool deleteAktual();
private:
	void removeAllClicked();
	void removeSelectedClicked();
	void doubleClickOnBoard(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
	bool on_button_clicked(GdkEventKey* evt);
	IndigoFile* copyFile(Gtk::TreeModel::Row &row);
	Gtk::ToggleButton* random;
	Gtk::ToggleButton* repeat;
	Gtk::ToggleButton* close;
	Gtk::Button* removeAll;
	Gtk::Button* removeSelected;
	Gtk::Entry* searchEntry;
	ModelColumns m_Columns;
	Gtk::TreeView *playlistBoard;
	Glib::RefPtr<Gtk::ListStore> playlistBoardModel;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::Row boardRow;
	PlayerSignals* signal;

	Gtk::TreeModel::Path pointer;
	Gtk::TreeModel::Row crRow;
	Gtk::TreeModel::Row lastAddSave;
	IndigoFile* crFile;

	bool isSetCurrentRow;
	PixbufPtr arrowImage;
	PixbufPtr clearImage;
	int numberOfRows;
	bool deleteAktualB;
};

#endif /* PLAYLISTGRAPHIC_H_ */
