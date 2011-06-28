/*
 * MainWindow.cpp
 *
 *  Created on: 24.6.2011
 *      Author: xgeier
 */

#include "MainWindow.h"
#include <gtkmm.h>


MainWindow::MainWindow(std::list<std::string> &files, PipeExchange *pip, Configuration *conf, std::string name, double version) {
	number = version;
	this->files = files;
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::show(){
	//std::stringstream ostr;
	//std::list<std::string>::iterator iterator;
	//for(iterator=files.begin();iterator!=files.end(); ++iterator) {
	//	ostr<<*iterator;
	//}
	//
	//Create new thred
	Gtk::Window window;
	Gtk::Entry enter;
	//enter.set_text(ostr.str());
	enter.set_visible(true);
	window.add(enter);
//	window.set_title(ostr.str());
	Gtk::Main::run(window);
}
