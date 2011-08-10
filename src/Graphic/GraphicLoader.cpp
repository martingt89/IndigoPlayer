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
		refBuilder->add_from_file(GLADEFILE);
	} catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
	} catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}

	refBuilder->get_widget_derived("BaseWindow", playerWindow);
	refBuilder->get_widget_derived("OpenWindow", openWindow);
	controlPanel = new ControlPanel(refBuilder);
	videoBoard = new VideoBoard(refBuilder, playerWindow);
	playlist = new PlaylistGraphic(refBuilder);
}

GraphicLoader::~GraphicLoader() {
	// TODO Auto-generated destructor stub
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
PlaylistGraphic* GraphicLoader::getPlaylistGraphic(){
	return playlist;
}
PlayerWindow *GraphicLoader::getPlayerWindow(){
	return playerWindow;
}
