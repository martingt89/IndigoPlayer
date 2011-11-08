/*
 * GraphicLoader.cpp
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 */

#include "GraphicLoader.h"

GraphicLoader::GraphicLoader()  throw (int){
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try {
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GPLAYERWINDOW));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GTHISOPTIONS));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GOPENDIALOG));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GCONTROLPANEL));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GOPENWINDOW));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GOPTIONSWIN));
	} catch (const Glib::FileError& ex) {
		log.log(IndigoLogger::FATAL, "Error load .glade files");
		log.log(IndigoLogger::FATAL, ex.what());
		throw -1;
	} catch (const Gtk::BuilderError& ex) {
		log.log(IndigoLogger::FATAL, "Error load .glade files");
		log.log(IndigoLogger::FATAL, ex.what());
		throw -1;
	}
	refBuilder->get_widget_derived("BaseWindow", playerWindow);
	refBuilder->get_widget_derived("OpenWindow", openWindow);
	refBuilder->get_widget_derived("OptionsWindow", optionsWindow);

	controlPanel = new ControlPanel(refBuilder);
	videoBoard = new VideoBoard(refBuilder);
	playlistLogic = new Playlist(new PlaylistGraphic(refBuilder));
	thisOptions = new ThisOptions(refBuilder);
	thisOptionsLoad = new ThisOptionsLoad(refBuilder);
}

GraphicLoader::~GraphicLoader() {
	delete playerWindow;
	delete openWindow;
	delete controlPanel;
	delete videoBoard;
	delete playlistLogic;
	delete thisOptions;
	delete thisOptionsLoad;
	delete optionsWindow;
}

ControlPanel* GraphicLoader::getBasePlayerWindow(){
	return controlPanel;
}
VideoBoard* GraphicLoader::getVideoBoard(){
	return videoBoard;
}
OpenFileDialog* GraphicLoader::getOpenDialog(){
	return openWindow;
}
Options* GraphicLoader::getOptionsWindow(){
	return optionsWindow;
}
Playlist* GraphicLoader::getPlaylist(){
	return playlistLogic;
}
PlayerWindow *GraphicLoader::getPlayerWindow(){
	return playerWindow;
}
ThisOptions *GraphicLoader::getThisOptions(){
	return thisOptions;
}
ThisOptionsLoad *GraphicLoader::getThisOptionsLoad(){
	return thisOptionsLoad;
}
