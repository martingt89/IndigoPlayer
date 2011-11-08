/*
 * OneInstance.cpp
 *
 *  Created on: 28.10.2011
 *      Author: martin89
 */

#include "OneInstance.h"

OneInstance::OneInstance(IndigoPlayer *_player) {
	player = _player;
	thr = NULL;
	stopReading = true;
}

bool OneInstance::lockInstance(bool &pipe) {
	pipe = true;
	Glib::ustring lockFile = pathLoader.getLockFilePath();
	instanceFd = open(lockFile.c_str(), O_RDWR | O_CREAT, 0644);
	if (instanceFd == -1) {
		pipe = false;
		return true; //cannot open or create file, run new instance
	}
	if (lockf(instanceFd, F_TLOCK, 0) == -1)
		return false; //cannot lock instace, write to pipe
	return true; //instance is main
}
void OneInstance::unlockInstance() {
	if (instanceFd == -1) {
		return; //nothing is open
	}
	if(lockf(instanceFd, F_ULOCK, 0) == -1){
		log.log(IndigoLogger::ALERT, "Cannot unlock instance lock");
	}
	close(instanceFd);
}

bool OneInstance::start(std::list<IndigoFile*> files) {
	stopReading = true;
	bool readFromPipe;
	if (lockInstance(readFromPipe)) {
		log.log(IndigoLogger::DEBUG, "Lock instance - I am master");
		if (readFromPipe) {
			player->addFiles(files, true);
			thr = Glib::Thread::create(sigc::mem_fun(this, &OneInstance::run),
					true);
			log.log(IndigoLogger::DEBUG, "running new thread for queue");
			return true;
		}
		log.log(IndigoLogger::CRIT,	"Cannot create one instace file: "+ pathLoader.getLockFilePath());
		return true;
	} else {
		log.log(IndigoLogger::DEBUG, "Cannot lock instance - I am slave");
		mqd_t mqPXId;

		if ((mqPXId = mq_open(pathLoader.getIProcessMQueueName().c_str(), O_WRONLY)) == -1) {
			log.log(IndigoLogger::CRIT, "Cannot open message queue: "
					+ pathLoader.getInterProcesPipePath() + " error: " + strerror(errno));
		} else {
			std::list<IndigoFile*>::iterator it;
			for (it = files.begin(); it != files.end(); it++)
				if (mq_send(mqPXId, (*it)->getFilePath().c_str(),
						strlen((*it)->getFilePath().c_str()) + 1, 16) == -1) {
					log.log(
							IndigoLogger::CRIT,
							"Cannot write to message queue: "
									+ std::string(strerror(errno)));
				} else {
					log.log(IndigoLogger::DEBUG,
							"Write to message queue: " + (*it)->getFilePath());
				}
			mq_send(mqPXId, "s", strlen("s") + 1, 16);
		}
	}
	return false;
}
void OneInstance::closeMQueue(){
	mqd_t mqPXId;
	if ((mqPXId = mq_open(pathLoader.getIProcessMQueueName().c_str(), O_WRONLY)) == -1) {
		log.log(IndigoLogger::CRIT,	"Cannot open message queue: " + pathLoader.getInterProcesPipePath()
				+ " error: " + strerror(errno));
	} else {
		if (mq_send(mqPXId, "q", strlen("q") + 1, 16) == -1) {
			log.log(IndigoLogger::CRIT, "Cannot write to message queue: " + std::string(strerror(errno)));
		} else {
			log.log(IndigoLogger::DEBUG, "Write to message queue: q");
		}
	}
}
void OneInstance::join() {
	if (!stopReading) {
		stopReading = true;
		if (thr){
			closeMQueue();
			thr->join();
		}
		unlockInstance();
	}
	thr = NULL;
}
void OneInstance::run() {
	stopReading = false;
	Glib::ustring fifoPath = pathLoader.getInterProcesPipePath();

	char ch;
	FileUtilities fu;

	int MAXSIZEBB = 200;

	mqd_t mqPXId;
	char msg[MAXSIZEBB]; /* msg buffer */
	unsigned int prio; /* priority of message */

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAXSIZEBB;
	attr.mq_curmsgs = 0;

	if ((mqPXId = mq_open(pathLoader.getIProcessMQueueName().c_str(), O_RDONLY | O_CREAT, 0644, &attr)) == -1) {
		log.log(IndigoLogger::CRIT, "Cannot open or create message queue: "+ std::string(strerror(errno)));
		return;
	}
	std::list<Glib::ustring> files;

	while (!stopReading) {
		std::list<IndigoFile*> uris;
		Glib::ustring text = "";

		/* try reading from queue */
		int recSize = 0;
		if ((recSize = mq_receive(mqPXId, msg, MAXSIZEBB, NULL)) != -1) {
			text = Glib::ustring(msg,0,recSize);
//			std::cout<<"text: "<<text<<" d "<<recSize<<std::endl;
			if(recSize == 2){
				if(text == "s"){
					if (files.size() != 0) {
						uris = fu.stringListToFiles(files, false, 0);
						player->addFiles(uris, true);
					}
					files.clear();
				}
				if(text == "q"){
					break;
				}
			}else
			files.push_back(text);
		} else {
			log.log(IndigoLogger::CRIT, "Cannot read from message queue: "+ std::string(strerror(errno)));
		}
	}
	mq_close(mqPXId);
	mq_unlink(pathLoader.getIProcessMQueueName().c_str());
}
