/*
 * OpenFileDialog.h
 *
 *  Created on: 3.8.2011
 *      Author: xgeier
 */

#ifndef OPENFILEDIALOG_H_
#define OPENFILEDIALOG_H_

#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/filechooserwidget.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/combobox.h>
#include <giomm/file.h>
#include "../Interfaces/PlayerSignals.h"

class OpenFileDialog: public Gtk::Window {
public:
	OpenFileDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~OpenFileDialog();
	void setListener(PlayerSignals* sig);
private:
	void playOpenFileClicked();
	void playOpenFolderClicked();
	void subDirectoryDepthChange();
	void clearWindow();

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::FileChooserWidget* openFileChooser;
	Gtk::FileChooserWidget* openFolderChooser;

	Gtk::Button* playOpenFile;
	Gtk::Button* playOpenFolder;
	Gtk::Button* playAdvencedOpen;
	Gtk::Button* openVideoFileAdvenced;
	Gtk::Button* openAudioFileAdvenced;
	Gtk::Button* openSubtitleFileAdvenced;

	Gtk::CheckButton* includeSubDirectory;

	Gtk::SpinButton* subDirectoriesDepth;
	Gtk::SpinButton* audioDelayAdvenced;
	Gtk::SpinButton* subtitleDelayAdvenced;

	Gtk::Entry* videoFilePathAdvenced;
	Gtk::Entry* audioFilePathAdvenced;
	Gtk::Entry* subtitleFilePathAdvenced;

	Gtk::ComboBox* subtitleFpsAdvenced;

	Gtk::Label* openFileWarningLabel;
	Gtk::Label* openFolderWarningLabel;
	Gtk::Label* advencetOpenWarningLabel;

	PlayerSignals* signal;
};

#endif /* OPENFILEDIALOG_H_ */
