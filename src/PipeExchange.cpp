#include "PipeExchange.h"

using namespace std;

PipeExchange::PipeExchange(std::string name, double version) {
	this->name = name;
	this->version = version;
	readPipe = -1;
	writePipe = -1;
	lock = -1;
	mysem = NULL;
}

PipeExchange::~PipeExchange() {
	if(lock >= 0){
		lockf(lock, F_ULOCK, 0);
		remove(getLockFilePath().c_str());
	}
	if(readPipe >= 0){
		close(readPipe);
		remove(getPipeFilePath().c_str());
	}
	close(writePipe);
}

bool PipeExchange::tryLock(){
	lock = open(getLockFilePath().c_str(), O_CREAT | O_WRONLY, 0644);
	if (lock >= 0) {
		cerr << "INFO: otvorili sme lock subor" << endl;

		int stat = lockf(lock, F_TLOCK, 0);
		if (stat == 0) {
			cerr << "INFO: zamkol som lock subor" << endl;
			return true;
		}
	}
	cerr << "INFO: neotvorili ani nevytvorili sme lock subor, subor je uz asi vytvoreny" << endl;
	return false;
}

bool PipeExchange::openWrite(){
	writePipe = open(getPipeFilePath().c_str(), O_WRONLY | O_APPEND);
	if(writePipe < 0)
			return false;
	return true;
}

bool PipeExchange::openRead(){
	if(mkfifo (getPipeFilePath().c_str(), 0666) < 0){
		if(errno != EEXIST){
			cerr<<"SEVERE: Nevytvorili sme pipu subor"<<endl;
			return false;
		}else{
			cerr<<"INFO: Pipa subor uz existuje"<<endl;
		}
	}
	cerr<<"INFO: uz mame pipa subor"<<endl;
	readPipe = open(getPipeFilePath().c_str(), O_RDONLY | O_NONBLOCK);
	if(readPipe < 0){
		cerr<<"SEVERE: Nepodarilo sa otvorit pipu na citanie"<<endl;
		return false;
	}
	cerr<<"INFO: otvorili sme pipa subor na citanie"<<endl;
	return true;
}

void PipeExchange::writeFiles(int argc, char *argv[]){

	//lock semaphore, write to pipe, send semaphore, unlock semaphore
}

std::string PipeExchange::getSemaphoreName(){
	std::stringstream ostr;
	ostr << name;
	ostr << version;
	ostr << "semaphore";
	return ostr.str();
}

std::string PipeExchange::getPipeFilePath(){
	std::stringstream ostr;
	ostr << getTemporaryPath();
	ostr << name;
	ostr << version;
	ostr << "pipe";
	return ostr.str();
}
std::string PipeExchange::getLockFilePath(){
	std::stringstream ostr;
	ostr << getTemporaryPath();
	ostr << name;
	ostr << version;
	ostr << "lock";
	return ostr.str();
}
std::string PipeExchange::getTemporaryPath(){
   const char *dir = getenv("TMPDIR");
   if(!dir){
      dir = getenv("TMP");
      if(!dir){
         dir = getenv("TEMP");
         if(!dir){
            dir = "/tmp";
         }
      }
   }
   std::string path(dir);
   if(path[path.length()] != '/'){
	   path += '/';
   }
   return path;
}
