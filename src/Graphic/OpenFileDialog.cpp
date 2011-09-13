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

	m_refGlade->get_widget("PlayOpenFile", playFile);
	m_refGlade->get_widget("OpenFileNotebook", openFileNotebook);

	m_refGlade->get_widget("OpenVideoFileAdvenced", openVideoFileAdvenced);
	m_refGlade->get_widget("OpenAudioFileAdvenced", openAudioFileAdvenced);
	m_refGlade->get_widget("OpenSubtitleFileAdvenced", openSubtitleFileAdvenced);

	m_refGlade->get_widget("IncludeSubDirectory", includeSubDirectory);

	m_refGlade->get_widget("SubDirectoriesDepth", subDirectoriesDepth);
	m_refGlade->get_widget("AudioDelayAdvenced", audioDelayAdvenced);
	m_refGlade->get_widget("SubtitleDelayAdvenced", subtitleDelayAdvenced);

	m_refGlade->get_widget("VideoFilePathAdvenced", videoFilePathAdvenced);
	m_refGlade->get_widget("AudioFilePathAdvenced", audioFilePathAdvenced);
	m_refGlade->get_widget("SubtitleFilePathAdvenced", subtitleFilePathAdvenced);
	m_refGlade->get_widget("UrlPath", urlPath);

	m_refGlade->get_widget("SubtitleFpsAdvenced", subtitleFpsAdvenced);

	m_refGlade->get_widget("OpenWarningLabel", openWarningLabel);

	Glib::ustring path = "";
	path = Glib::get_user_special_dir(G_USER_DIRECTORY_VIDEOS);
	if (path.size() == 0) {
		path = Glib::get_home_dir();
	}
	if (path.size() != 0) {
		openFileChooser->set_current_folder(path);
		openFolderChooser->set_current_folder(path);
	}

	openFileChooser->signal_file_activated().connect(sigc::mem_fun(this, &OpenFileDialog::openFileClicked));
	playFile->signal_clicked().connect(sigc::mem_fun(this, &OpenFileDialog::playFileClicked));
	this->signal_hide().connect(sigc::mem_fun(this, &OpenFileDialog::clearWindow));
	openFileNotebook->signal_switch_page().connect(sigc::mem_fun(this, &OpenFileDialog::switchPage));

	subDirectoriesDepth->signal_value_changed().connect(
			sigc::mem_fun(this, &OpenFileDialog::subDirectoryDepthChange));

	openVideoFileAdvenced->signal_clicked().connect(sigc::mem_fun(this, &OpenFileDialog::openVideoClicked));
	openAudioFileAdvenced->signal_clicked().connect(sigc::mem_fun(this, &OpenFileDialog::openAudioClicked));
	openSubtitleFileAdvenced->signal_clicked().connect(
			sigc::mem_fun(this, &OpenFileDialog::openSubtitleClicked));
}
void OpenFileDialog::setListener(PlayerSignals* sig) {
	signal = sig;
}
void OpenFileDialog::showOn(){
	openFileNotebook->set_current_page(0);
	this->show();
}
void OpenFileDialog::clearWindow() {
	openWarningLabel->set_markup("");
	fileChooser.clear();
	videoFilePathAdvenced->set_text("");
	audioFilePathAdvenced->set_text("");
	subtitleFilePathAdvenced->set_text("");
}
void OpenFileDialog::switchPage(GtkNotebookPage* page, guint pageNum) {
	openWarningLabel->set_markup("");
}
void OpenFileDialog::openVideoClicked() {
	videoFilePathAdvenced->set_text(fileChooser.showFileChooser("Select video file"));
	fileChooser.hide();
}
void OpenFileDialog::openAudioClicked() {
	audioFilePathAdvenced->set_text(fileChooser.showFileChooser("Select audio file"));
	fileChooser.hide();
}
void OpenFileDialog::openSubtitleClicked() {
	subtitleFilePathAdvenced->set_text(fileChooser.showFileChooser("Select subtitle file"));
	fileChooser.hide();
}
void OpenFileDialog::playFileClicked() {
	if (signal == 0) {
		this->hide();
	} else {
		if (getOpenPage() == IndigoPlayerEnum::FILE)
			openFileClicked();
		if (getOpenPage() == IndigoPlayerEnum::FOLDER)
			openFolderClicked();
		if (getOpenPage() == IndigoPlayerEnum::NETWORK)
			openURLClicked();
		if (getOpenPage() == IndigoPlayerEnum::ANDVENCEDFILE)
			openAdvencedClicked();
	}
}
void OpenFileDialog::openURLClicked() {
	Glib::ustring path = urlPath->get_text();
	if (path.size() == 0) {
		Glib::ustring warning = "You must enter an address";
		openWarningLabel->set_markup("<span color=\"red\">" + warning + "</span>");
	} else {
		std::list<IndigoFile*> finalFilesList;
		finalFilesList.push_back(new IndigoFile(path, IndigoFileType::URL));
		signal->addFiles(finalFilesList, true);
		this->hide();
	}
}
void OpenFileDialog::openAdvencedClicked() {
	if (helperFunctions.trimText(videoFilePathAdvenced->get_text()).size() == 0) {
		openVideoClicked();
	} else {
		std::list<IndigoFile*> finalFilesList;
		IndigoFile* file = new IndigoFile(helperFunctions.trimText(videoFilePathAdvenced->get_text()), IndigoFileType::UNKNOWN);
		file->setSoundDelayms(audioDelayAdvenced->get_value_as_int());
		file->setSoundFile(helperFunctions.trimText(audioFilePathAdvenced->get_text()));
		file->setSubtitleDelayms(subtitleDelayAdvenced->get_value_as_int());
		file->setSubtitleFile(helperFunctions.trimText(subtitleFilePathAdvenced->get_text()));
		finalFilesList.push_back(file);
		signal->addFiles(finalFilesList, true);
		this->hide();
	}
}
void OpenFileDialog::openFolderClicked() {
	std::vector<Glib::RefPtr<Gio::File> > files = openFolderChooser->get_files();
	Glib::ustring current = openFolderChooser->get_current_folder();
	std::list<Glib::ustring> regularFiles;
	for (unsigned int i = 0; i < files.size(); i++) {
			regularFiles.push_back(files[i]->get_path());
	}
	if (regularFiles.size() == 0) {
		Glib::ustring warning = "You must choose minimal one folder";
		openWarningLabel->set_markup("<span color=\"red\">" + warning + "</span>");
	} else {
		std::list<IndigoFile*> finalFilesList;
		FileUtilities fu;
		int deb = 0;
		if (includeSubDirectory->get_active())
			deb = subDirectoriesDepth->get_value_as_int();
		finalFilesList = fu.stringListToFiles(regularFiles, true, deb);
		signal->addFiles(finalFilesList, true);
		this->hide();
	}
}
void OpenFileDialog::openFileClicked() {
	std::vector<Glib::RefPtr<Gio::File> > files = openFileChooser->get_files();
	std::list<Glib::ustring> regularFiles;
	for (unsigned int i = 0; i < files.size(); i++) {
		if (files[i]->query_file_type() == Gio::FILE_TYPE_REGULAR) {
			regularFiles.push_back(files[i]->get_path());
		}
	}
	if (regularFiles.size() == 0) {
		Glib::ustring warning = "You must choose minimal one file";
		openWarningLabel->set_markup("<span color=\"red\">" + warning + "</span>");
	} else {
		std::list<IndigoFile*> finalFilesList;
		FileUtilities fu;
		finalFilesList = fu.stringListToFiles(regularFiles, false);
		signal->addFiles(finalFilesList, true);
		this->hide();
	}
}

void OpenFileDialog::subDirectoryDepthChange() {
	includeSubDirectory->set_active(true);
}
IndigoPlayerEnum::OpenWindowNotebook OpenFileDialog::getOpenPage() {
	IndigoPlayerEnum::OpenWindowNotebook type;
	switch (openFileNotebook->get_current_page()) {
	case 0:
		type = IndigoPlayerEnum::FILE;
		break;
	case 1:
		type = IndigoPlayerEnum::FOLDER;
		break;
	case 2:
		type = IndigoPlayerEnum::ANDVENCEDFILE;
		break;
	case 3:
		type = IndigoPlayerEnum::NETWORK;
		break;
	case 4:
		type = IndigoPlayerEnum::DVD;
		break;
	default:
		type = IndigoPlayerEnum::FILE;
		break;
	}
	return type;
}
OpenFileDialog::~OpenFileDialog() {
	// TODO delete gtk objects
}

