#include <iostream>
#include <string>

#include <gtkmm.h>

#include "Settings.h"
#include "src/Communication/ExclusiveLock.h"
#include "src/Communication/PipeExchange.h"
#include "src/Configuration.h"
#include "src/Graphic/MainWindow.h"


int main(int argc, char *argv[]){
	Gtk::Main kit(argc, argv);

	Configuration *config = new Configuration(NAME, VERSION);
	MainWindow *window = NULL;
	if(config->onlyOne()){	//vypliva z konfiguracie
		PipeExchange *pip = new  PipeExchange(NAME, VERSION);
		ProgramUtilitys util;
		ExclusiveLock instanceLock(util.getInstanceLockFilePath(), false);
		if(instanceLock.tryLockFile()){
			//sme prva instancia
			if(pip->openRead()){
			//	pip->readCommand();
				window = new MainWindow(pip, config, NAME, argc);
				window->show();
			}else{
				std::cerr<<"SEVERE: Ziskali sme lock ale nie je mozne otvorit pipu na citanie"<<std::endl;
				return -1;
			}
		}else{
			//nie sme prva instancia
			if(pip->openWrite()){
				std::cerr<<"INFO: Otvorili sme pipu na zapis"<<std::endl;
				pip->writeFiles(argc, argv);
			}else{
				std::cerr<<"SEVERE: Nemame lock a ani sme neziskali pipu na zapis"<<std::endl;
				return -1;
			}
		}
		instanceLock.unlockFile();
	}else{
		window = new MainWindow(NULL, config, NAME, VERSION);
		window->show();
	}
	//clean
	if(window)
		delete window;
	delete config;
	return 0;
}
