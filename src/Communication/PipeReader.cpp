/*
 * PipeReader.cpp
 *
 *  Created on: 30.6.2011
 *      Author: xgeier
 */

#include "PipeReader.h"

PipeReader::PipeReader(PipeExchange *pip) {
	this->pipe = pip;
}

PipeReader::~PipeReader() {

}

void PipeReader::start(){
	//not so easy, potrebne este casovace
//	while(true){
//		std::string command = pipe->readMessage();
//		std::cout<<command<<std::endl;
//		if(command == "0"){
//			window->showUp();
//		}else{
//			//convert string to list
//			//window->addFiles(list);
//		}
//	}
}
