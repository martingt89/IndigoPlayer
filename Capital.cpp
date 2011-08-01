#include <iostream>
#include <string>
#include <list>

#include <gtkmm.h>

#include <glibmm/random.h>
#include <glibmm/thread.h>
#include <glibmm/timer.h>

#include "Settings.h"

#include "src/Configuration.h"

#include "src/Communication/ExclusiveLock.h"
#include "src/Communication/PipeExchange.h"
#include "src/Communication/PipeReader.h"

#include "src/Graphic/GraphicLoader.h"

#include "src/Player/Player.h"
#include "src/Communication/ConfigFile.h"



int main(int argc, char *argv[]){
	Glib::thread_init();
	Gtk::Main kit(argc, argv);
	std::list<std::string> zoznam;
	for(int i = 1; i < argc; i++){
		zoznam.push_back(std::string(argv[i]));
	}

	ConfigFile file;

	GraphicLoader *gLoader = new GraphicLoader();
	Player *player = new Player(gLoader->getBasePlayerWindow());

	Gtk::Main::run(*(gLoader->getBasePlayerWindow()));

	delete gLoader;
	delete player;
	return 0;
}

/*

	Configuration *config = new Configuration(NAME, VERSION);
//	MainWindow *window = NULL;
	if(config->onlyOne()){	//vypliva z konfiguracie
		PipeExchange *pip = new  PipeExchange(NAME, VERSION);
		ProgramUtilitys util;
		ExclusiveLock instanceLock(util.getInstanceLockFilePath(), false);
		if(instanceLock.tryLockFile()){
			if(pip->createPipe()){
			//	window = new MainWindow(config);
			//	window->addFiles(zoznam);
			//	PipeReader reader(pip, window);
				//Glib::Thread *const producer =
				Glib::Thread::create(sigc::mem_fun(reader, &PipeReader::start), false);

				std::cerr<<"INFO: Vytvorili sme pipu"<<std::endl;

			//	window->show();
				pip->removePipe();
			}else{
				std::cerr<<"SEVERE: Nie je mozne vytvorit pipa subor"<<std::endl;
			}
		}else{
			if(!pip->writeFiles(argc, argv)){
				std::cerr<<"SEVERE: Nepodarilo sa subor poslat"<<std::endl;
			}
		}
		instanceLock.unlockFile();
	}else{
//		window = new MainWindow(config);
//		window->addFiles(zoznam);
//		window->show();
	}
//	if(window)
//		delete window;
	delete config;
	*/

