/*
 * MainWindow.h
 *
 *  Created on: 24.6.2011
 *      Author: xgeier
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

//#include <sstream>

#include "../Configuration.h"
#include "../PipeExchange.h"


class MainWindow {
public:
	MainWindow(PipeExchange *pip, Configuration *conf, std::string name, double version);
	virtual ~MainWindow();
	void show();
private:
	int number;
};

#endif /* MAINWINDOW_H_ */
