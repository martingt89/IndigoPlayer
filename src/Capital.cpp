#include <iostream>
#include <string>
#include <list>

#include <glibmm/random.h>
#include <glibmm/thread.h>
#include <glibmm/timer.h>
#include <gtkmm/main.h>

#include "Settings.h"

#include "Player/IndigoPlayer.h"
#include "GraphicLogic/WindowBridge.h"
#include "GraphicLogic/GraphicLoader.h"
#include "Files/Logger.h"
#include "Files/FileUtilities.h"
#include "ConfigFile.h"

int main(int argc, char *argv[]){
	std::cout<<" "<<GLADECONTROLPANEL<<std::endl;
	Glib::thread_init();
	Gtk::Main kit(argc, argv);
	FileUtilities fu;
	fu.createFolderSkeleton(INDIGONAME, LOGFOLDER);
	IndigoLogger::Logger log;
	log.log(IndigoLogger::DEBUG, "Starting main with "+Glib::ustring::format(argc)+" parameters");
	std::list<Glib::ustring>::iterator listIter2;
	std::list<Glib::ustring> files;
	std::list<IndigoFile*> uris;

	for (int i = 1; i < argc; i++) {
		if(std::string(argv[i]).size()>0)
			files.push_back(std::string(argv[i]));
	}
	if(files.size() > 0){
		uris = fu.stringListToFiles(files, true, 0);
	}
	ConfigFile file();

	GraphicLoader *gLoader = new GraphicLoader();
	OneFilePlayer* filePlayer = new OneFilePlayer();
	IndigoPlayer *player = new IndigoPlayer(gLoader->getPlayerWindow(), filePlayer);
	player->setControlPanel(gLoader->getBasePlayerWindow());
	player->setVideoBoard(gLoader->getVideoBoard());
	player->setPlaylist(gLoader->getPlaylist());
	player->setOpenDialog(gLoader->getOpenDialog());
	player->setThisOptions(gLoader->getThisOptions());
	player->setThisOptionsLoad(gLoader->getThisOptionsLoad());

	WindowBridge bridge;
	bridge.addCallable(filePlayer);
	bridge.setPlayerWindow(gLoader->getPlayerWindow());
	bridge.setControlPanel(gLoader->getBasePlayerWindow());
	bridge.setVideoBoard(gLoader->getVideoBoard());
	bridge.setPlaylist(gLoader->getPlaylist());
	bridge.setOpenDialog(gLoader->getOpenDialog());
	bridge.setThisOptions(gLoader->getThisOptions());
	bridge.setThisOptionsLoad(gLoader->getThisOptionsLoad());

	if(uris.size()> 0)
		player->addFiles(uris, true);
	Gtk::Main::run();
	delete gLoader;
	delete player;
	log.log(IndigoLogger::DEBUG, "Ending main");
	return 0;
}
