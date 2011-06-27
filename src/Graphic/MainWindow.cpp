/*
 * MainWindow.cpp
 *
 *  Created on: 24.6.2011
 *      Author: xgeier
 */

#include "MainWindow.h"
#include <gtkmm.h>

MainWindow::MainWindow(PipeExchange *pip, Configuration *conf, std::string name, double version) {
	number = version;
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::show(){
//	std::stringstream ostr;
//	ostr<<number;

	Gtk::Window window;
//	window.set_title(ostr.str());
	Gtk::Main::run(window);
}
