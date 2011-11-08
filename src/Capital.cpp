#include <iostream>
#include <string>
#include <list>

#include <glibmm/random.h>
#include <glibmm/thread.h>
#include <glibmm/timer.h>
#include <gtkmm/main.h>

#include <libintl.h>
#include <config.h>

#include "Settings.h"
#include "ConfigFile.h"

#include "Player/IndigoPlayer.h"
#include "GraphicLogic/WindowBridge.h"
#include "GraphicLogic/GraphicLoader.h"
#include "Files/Logger.h"
#include "Files/FileUtilities.h"
#include "OneInstance.h"

int main(int argc, char *argv[]){

	bindtextdomain(GETTEXT_PACKAGE, DATADIR"/locale");
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

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
	ConfigFile file;
	GraphicLoader *gLoader = NULL;
	try{
		gLoader = new GraphicLoader();
	}catch( int ie ) {
		std::cout<<"Cannot load graphic files: see log files"<<std::endl;
		return -1;
	}
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
	bridge.setOptions(gLoader->getOptionsWindow());
	bridge.setPlayerWindow(gLoader->getPlayerWindow());
	bridge.setControlPanel(gLoader->getBasePlayerWindow());
	bridge.setVideoBoard(gLoader->getVideoBoard());
	bridge.setPlaylist(gLoader->getPlaylist());
	bridge.setOpenDialog(gLoader->getOpenDialog());
	bridge.setThisOptions(gLoader->getThisOptions());
	bridge.setThisOptionsLoad(gLoader->getThisOptionsLoad());
	
	bool instance = file.getAsBool(IndigoConfig::ONEINSTANCE);
	bool runGraphic = true;
	OneInstance one(player);
	if(instance){
		runGraphic = one.start(uris);
	}else{
		if(uris.size() > 0)
			player->addFiles(uris, true);
	}
	if(runGraphic){
		Gtk::Main::run();
	}
	one.join();
	delete gLoader;
	delete player;
	log.log(IndigoLogger::DEBUG, "Ending main");
	return 0;
}
