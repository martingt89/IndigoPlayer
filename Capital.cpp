#include <iostream>
#include <string>

#include <gtkmm.h>

#include "src/PipeExchange.h"
#include "src/Configuration.h"
#include "src/Graphic/MainWindow.h"

#define NAME "IndigoPlayer"
#define VERSION 0.1


int main(int argc, char *argv[]){
	Gtk::Main kit(argc, argv);

	Configuration *config = new Configuration(NAME, VERSION);
	MainWindow *window;
	if(config->onlyOne()){	//vypliva z konfiguracie
		PipeExchange *pip = new  PipeExchange(NAME, VERSION);
		if(pip->tryLock()){
			//sme prva instancia
			if(pip->openRead()){
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
	}else{
		window = new MainWindow(NULL, config, NAME, VERSION);
		window->show();
	}

	delete window;
	delete config;
	return 0;
}
