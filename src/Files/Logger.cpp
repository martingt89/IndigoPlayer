/*
 * Logger.cpp
 *
 *  Created on: 7.9.2011
 *      Author: martin89
 */

#include "Logger.h"

std::map<Glib::ustring, bool> IndigoLogger::Logger::init;

IndigoLogger::Logger::Logger(Glib::ustring prefix)
	: category(log4cpp::Category::getInstance(prefix+"Category")) {
	if(init.find(prefix) == init.end()){
		Glib::ustring path;
		if(path.c_str()[path.size()] != '/')
			path+="/";
		config.get(IndigoConfig::LOGPATH, path);
		Glib::ustring name;
		config.get(IndigoConfig::LOGFILENAME, name);
		name = path + prefix + name;
		init[prefix] = true;
		log4cpp::Appender *appender = new log4cpp::FileAppender(prefix+"FileAppender", name, false);
		log4cpp::Layout *layout = new log4cpp::BasicLayout();

		appender->setLayout(layout);
		category.setAppender(appender);
		category.setPriority(log4cpp::Priority::DEBUG);
	}
}

IndigoLogger::Logger::~Logger() {
}

void IndigoLogger::Logger::log(IndigoLogger::Level level, Glib::ustring logText){
	switch(level){
	case IndigoLogger::DEBUG:
		category.debug(logText);
		break;
	case IndigoLogger::INFO:
		category.info(logText);
		break;
	case IndigoLogger::NOTICE:
		category.notice(logText);
		break;
	case IndigoLogger::WARN:
		category.warn(logText);
		break;
	case IndigoLogger::ERROR:
		category.error(logText);
		break;
	case IndigoLogger::CRIT:
		category.crit(logText);
		break;
	case IndigoLogger::ALERT:
		category.alert(logText);
		break;
	case IndigoLogger::FATAL:
		category.fatal(logText);
		break;
	default:
		category.fatal(logText);
		break;
	}
}
