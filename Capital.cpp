#include <iostream>
#include <string>
#include <list>

#include <glibmm/random.h>
#include <glibmm/thread.h>
#include <glibmm/timer.h>
#include <gtkmm/main.h>

#include "Settings.h"
#include "src/Graphic/GraphicLoader.h"

#include "src/Player/IndigoPlayer.h"


int main(int argc, char *argv[]){
	Glib::thread_init();
	Gtk::Main kit(argc, argv);
	std::list<Glib::ustring>::iterator listIter2;
	std::list<IndigoFile*> uris;
	FileUtilities fu;
	for (int i = 1; i < argc; i++) {
		std::list<Glib::ustring> ma = fu.fileToPlaylist(std::string(argv[i]));
		for(listIter2 = ma.begin(); listIter2 != ma.end(); listIter2++)
			uris.push_back(new IndigoFile(*listIter2, true));
	}
	ConfigFile file(true);

	GraphicLoader *gLoader = new GraphicLoader();
	IndigoPlayer *player = new IndigoPlayer(gLoader->getPlayerWindow());
	player->setControlPanel(gLoader->getBasePlayerWindow());
	player->setVideoBoard(gLoader->getVideoBoard());
	player->setPlaylist(new Playlist(gLoader->getPlaylistGraphic()));
	player->setOpenDialog(gLoader->getOpenDialog());
	player->setThisOptions(gLoader->getThisOptions());
	if(uris.size()> 0)
		player->addFiles(uris, true);

	//Gtk::Main::run(*(gLoader->getPlayerWindow()));
	Gtk::Main::run();
	delete gLoader;
	delete player;
	return 0;
}
