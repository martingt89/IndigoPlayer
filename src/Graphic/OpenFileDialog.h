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
#include <gtkmm/notebook.h>
#include "../Interfaces/PlayerSignals.h"
#include "../MyWidget/FileChoosers.h"
#include "../ClassHelper/ClassHelper.h"
#include "../../EnumTypes.h"

class OpenFileDialog: public Gtk::Window {
public:
	OpenFileDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~OpenFileDialog();
	void setListener(PlayerSignals* sig);
	void showOn();
private:
	void openFileClicked();
	void openFolderClicked();
	void openURLClicked();
	void openAdvencedClicked();
	void subDirectoryDepthChange();
	void clearWindow();
	void switchPage(GtkNotebookPage* page, guint pageNum);
	void playFileClicked();
	void openVideoClicked();
	void openAudioClicked();
	void openSubtitleClicked();
	IndigoPlayerEnum::OpenWindowNotebook getOpenPage();

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::FileChooserWidget* openFileChooser;
	Gtk::FileChooserWidget* openFolderChooser;
	Gtk::Notebook* openFileNotebook;

	Gtk::Button* playFile;
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

	Gtk::Entry* urlPath;
	Gtk::ComboBox* subtitleFpsAdvenced;
	Gtk::Label* openWarningLabel;

	PlayerSignals* signal;
	FileChoosers fileChooser;
	ClassHelper helperFunctions;
};

#endif /* OPENFILEDIALOG_H_ */
