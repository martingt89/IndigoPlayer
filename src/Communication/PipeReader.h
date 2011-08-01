/*
 * PipeReader.h
 *
 *  Created on: 30.6.2011
 *      Author: xgeier
 */

#ifndef PIPEREADER_H_
#define PIPEREADER_H_

#include "PipeExchange.h"
#include <string>

#include <iostream>

#include "../../Settings.h"

class PipeReader {
public:
	PipeReader(PipeExchange *pip);
	virtual ~PipeReader();
	void start();
private:
//	MainWindow *window;
	PipeExchange *pipe;
};

#endif /* PIPEREADER_H_ */
