#include <iostream>
#include <string>

#include <gtkmm.h>

#include "Settings.h"
#include "src/Configuration.h"
#include "src/Communication/ExclusiveLock.h"
#include "src/Communication/PipeExchange.h"
#include "src/Graphic/MainWindow.h"

#include <list>

int main(int argc, char *argv[]){
	Gtk::Main kit(argc, argv);
	std::list<std::string> zoznam;
	for(int i = 1; i < argc; i++){
		zoznam.push_back(std::string(argv[i]));
	}
	Configuration *config = new Configuration(NAME, VERSION);
	MainWindow *window = NULL;
	if(config->onlyOne()){	//vypliva z konfiguracie
		PipeExchange *pip = new  PipeExchange(NAME, VERSION);
		ProgramUtilitys util;
		ExclusiveLock instanceLock(util.getInstanceLockFilePath(), false);
		if(instanceLock.tryLockFile()){
			if(pip->createPipe()){
		//		std::cout<<pip->readCommand()<<std::endl;
				std::cerr<<"INFO: Vytvorili sme pipu"<<std::endl;
				window = new MainWindow(zoznam, pip, config, NAME, VERSION);
				window->show();
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
		window = new MainWindow(zoznam, NULL, config, NAME, VERSION);
		window->show();
	}
	if(window)
		delete window;
	delete config;
	return 0;
}
