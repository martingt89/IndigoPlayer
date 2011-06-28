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
	readPipe = open(util.getPipeFilePath().c_str(), O_RDONLY);
	if(readPipe < 0){
		cerr<<"SEVERE: Nepodarilo sa otvorit pipu na citanie"<<endl;
		return NULL;
	}
	cerr<<"INFO: otvorili sme pipa subor na citanie"<<endl;
	char buffer[128];
	stringstream text;
	int len = 0;
	text << "";

	while((len = read(readPipe, buffer, 128)) > 0){
		buffer[len] = '\0';
		text << buffer;
	}
	close(readPipe);
	return text.str();
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

bool PipeExchange::writeFiles(int argc, char *argv[]){
	ExclusiveLock writeLock(util.getPipeLockFilePath(), true);
	if(writeLock.tryLockFile()){

		writePipe = open(util.getPipeFilePath().c_str(), O_WRONLY | O_APPEND);
		if(writePipe < 0) return false;

		if(argc == 1){
			write(writePipe, "empty", strlen("empty"));
		}else
		for(int i = 1; i < argc; i++){
			write(writePipe, argv[i], strlen(argv[i]));
			write(writePipe, "\n", strlen("\n"));
		}
		writeLock.unlockFile();
		close(writePipe);
		return true;
	}else{
		cerr<<"SEVERE: cannot lock pipe"<<endl;
	}
	return false;
}
