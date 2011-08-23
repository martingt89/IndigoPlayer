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
	std::list<Glib::ustring> files;
	std::list<IndigoFile*> uris;
	FileUtilities fu;
	for (int i = 1; i < argc; i++) {
		files.push_back(std::string(argv[i]));
	}
	uris = fu.stringListToFiles(files, true);
	ConfigFile file(true);

	GraphicLoader *gLoader = new GraphicLoader();
	IndigoPlayer *player = new IndigoPlayer(gLoader->getPlayerWindow());
	player->setControlPanel(gLoader->getBasePlayerWindow());
	player->setVideoBoard(gLoader->getVideoBoard());
	player->setPlaylist(new Playlist(gLoader->getPlaylistGraphic()));
	player->setOpenDialog(gLoader->getOpenDialog());
	player->setThisOptions(gLoader->getThisOptions());
	player->setThisOptionsLoad(gLoader->getThisOptionsLoad());
	if(uris.size()> 0)
		player->addFiles(uris, true);
	Gtk::Main::run();
	delete gLoader;
	delete player;
	return 0;
}
