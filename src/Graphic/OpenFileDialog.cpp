/*
 * OpenFileDialog.cpp
 *
 *  Created on: 3.8.2011
 *      Author: xgeier
 */

#include "OpenFileDialog.h"
#include <iostream>
#include <iterator>
#include <list>
#include <glibmm/ustring.h>
#include "../Files/FileUtilities.h"

OpenFileDialog::OpenFileDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
		Gtk::Window(cobject), m_refGlade(refGlade) {
	signal = 0;
	m_refGlade->get_widget("FileChooserOpenFile", openFileChooser);
	m_refGlade->get_widget("FileChooserOpenFolder", openFolderChooser);

	m_refGlade->get_widget("PlayOpenFile", playOpenFile);
	m_refGlade->get_widget("PlayOpenFolder", playOpenFolder);
	m_refGlade->get_widget("PlayAdvencedOpen", playAdvencedOpen);
	m_refGlade->get_widget("OpenVideoFileAdvenced", openVideoFileAdvenced);
	m_refGlade->get_widget("OpenAudioFileAdvenced", openAudioFileAdvenced);
	m_refGlade->get_widget("OpenSubtitleFileAdvenced", openSubtitleFileAdvenced);

	m_refGlade->get_widget("IncludeSubDirectory", includeSubDirectory);

	m_refGlade->get_widget("SubDirectoriesDepth", subDirectoriesDepth);
	m_refGlade->get_widget("AudioDelayAdvenced", audioDelayAdvenced);
	m_refGlade->get_widget("SubtitleDelayAdvenced", subtitleDelayAdvenced);

	m_refGlade->get_widget("SubtitleFpsAdvenced", subtitleFpsAdvenced);

	m_refGlade->get_widget("OpenFileWarningLabel", openFileWarningLabel);
	m_refGlade->get_widget("OpenFolderWarningLabel", openFolderWarningLabel);
	m_refGlade->get_widget("AdvencetOpenWarningLabel", advencetOpenWarningLabel);

	openFileChooser->signal_file_activated().connect(
			sigc::mem_fun(this, &OpenFileDialog::playOpenFileClicked));
	playOpenFile->signal_clicked().connect(sigc::mem_fun(this, &OpenFileDialog::playOpenFileClicked));
	playOpenFolder->signal_clicked().connect(sigc::mem_fun(this, &OpenFileDialog::playOpenFolderClicked));
	this->signal_hide().connect(sigc::mem_fun(this, &OpenFileDialog::clearWindow));
//	playAdvencedOpen
//	openVideoFileAdvenced
//	openAudioFileAdvenced
//	openSubtitleFileAdvenced

	subDirectoriesDepth->signal_value_changed().connect(
			sigc::mem_fun(this, &OpenFileDialog::subDirectoryDepthChange));
}
void OpenFileDialog::setListener(PlayerSignals* sig) {
	signal = sig;
}
void OpenFileDialog::clearWindow() {
	openFileWarningLabel->set_markup("");
	openFolderWarningLabel->set_markup("");
	advencetOpenWarningLabel->set_markup("");
}
void OpenFileDialog::playOpenFileClicked() {
	if (signal == 0) {
		this->hide();
	} else {
		std::vector<Glib::RefPtr<Gio::File> > files = openFileChooser->get_files();
		std::list<Glib::ustring> regularFiles;
		for (unsigned int i = 0; i < files.size(); i++) {
			if (files[i]->query_file_type() == Gio::FILE_TYPE_REGULAR){
				regularFiles.push_back(files[i]->get_path());
			}
		}
		if (regularFiles.size() == 0) {
			Glib::ustring warning = "You must choose minimal one file";
			openFileWarningLabel->set_markup("<span color=\"red\">" + warning + "</span>");
		} else {
			std::list<Glib::ustring>::iterator listIterator;
			std::list<Glib::ustring>::iterator listIter2;
			std::list<IndigoFile*> finalFilesList;
			FileUtilities fu;
			for(listIterator = regularFiles.begin(); listIterator!= regularFiles.end(); listIterator++){
				std::list<Glib::ustring> ma = fu.fileToPlaylist(*listIterator);
				for(listIter2 = ma.begin(); listIter2 != ma.end(); listIter2++)
					finalFilesList.push_back(new IndigoFile(*listIter2, true));
			}
			signal->addFiles(finalFilesList, true);
			this->hide();
		}
	}
}
void OpenFileDialog::playOpenFolderClicked() {

}
void OpenFileDialog::subDirectoryDepthChange() {
	includeSubDirectory->set_active(true);
}
OpenFileDialog::~OpenFileDialog() {
	//delete
}

