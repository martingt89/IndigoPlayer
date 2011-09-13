/*
 * GraphicLoader.cpp
 *
 *  Created on: 20.7.2011
 *      Author: xgeier
 */

#include "GraphicLoader.h"

GraphicLoader::GraphicLoader() {
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try {
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GPLAYERWINDOW));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GTHISOPTIONS));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GOPENDIALOG));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GCONTROLPANEL));
		refBuilder->add_from_file(pathLoader.getPath(IndigoPath::GOPENWINDOW));
	} catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
	} catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}

	refBuilder->get_widget_derived("BaseWindow", playerWindow);
	refBuilder->get_widget_derived("OpenWindow", openWindow);
	controlPanel = new ControlPanel(refBuilder);
	videoBoard = new VideoBoard(refBuilder);
	PlaylistGraphic* playlist = new PlaylistGraphic(refBuilder);
	thisOptions = new ThisOptions(refBuilder);
	thisOptionsLoad = new ThisOptionsLoad(refBuilder);
	playlistLogic = new Playlist(playlist);
}

GraphicLoader::~GraphicLoader() {
	delete playerWindow;
	delete openWindow;
	delete controlPanel;
	delete videoBoard;
	delete playlistLogic;
	delete thisOptions;
	delete thisOptionsLoad;
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
