#include "PipeExchange.h"

using namespace std;

PipeExchange::PipeExchange(std::string name, double version) {
	this->name = name;
	this->version = version;
	readPipe = -1;
	writePipe = -1;
}

PipeExchange::~PipeExchange() {
	if(readPipe >= 0){
		close(readPipe);
	}
	close(writePipe);
}

std::string PipeExchange::readCommand(){
	int i;
	char buffer[128];

	i = read(readPipe, buffer, 128);
	cout<<"pocet nacitanych: "<<i<<std::endl;
	return "nic";
}

bool PipeExchange::openWrite(){
	writePipe = open(util.getPipeFilePath().c_str(), O_WRONLY | O_APPEND);
	if(writePipe < 0)
			return false;
	return true;
}

bool PipeExchange::openRead(){
	readPipe = open(util.getPipeFilePath().c_str(), O_RDONLY);
	if(readPipe < 0){
		cerr<<"SEVERE: Nepodarilo sa otvorit pipu na citanie"<<endl;
		return false;
	}
	cerr<<"INFO: otvorili sme pipa subor na citanie"<<endl;
	return true;
}

bool PipeExchange::createPipe(){
	if(mkfifo (util.getPipeFilePath().c_str(), 0666) < 0){
		if(errno != EEXIST){
			cerr<<"SEVERE: Nevytvorili sme pipu subor"<<endl;
			return false;
		}else{
			cerr<<"INFO: Pipa subor uz existuje"<<endl;
		}
	}
	return true;
}

void PipeExchange::removePipe(){
	remove(util.getPipeFilePath().c_str());
}

void PipeExchange::writeFiles(int argc, char *argv[]){

	//lock file, write to pipe, send semaphore, unlock file
}
