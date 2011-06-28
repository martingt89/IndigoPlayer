/*
 * MainWindow.h
 *
 *  Created on: 24.6.2011
 *      Author: xgeier
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

//#include <sstream>
#include <list>
#include <iterator>

#include "../Configuration.h"
#include "../Communication/PipeExchange.h"


class MainWindow {
public:
	MainWindow(std::list<std::string> &files, PipeExchange *pip, Configuration *conf, std::string name, double version);
	virtual ~MainWindow();
	void show();
private:
	int number;
	std::list<std::string> files;
};

#endif /* MAINWINDOW_H_ */
