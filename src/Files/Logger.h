/*
 * Logger.h
 *
 *  Created on: 7.9.2011
 *      Author: martin89
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <glibmm/ustring.h>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#include "../ConfigFile.h"

namespace IndigoLogger {
enum Level {
	DEBUG, INFO, NOTICE, WARN, ERROR, CRIT, ALERT, FATAL
};

class Logger {
public:
	Logger(Glib::ustring prefix="");
	virtual ~Logger();
	void log(IndigoLogger::Level level, Glib::ustring logText);
private:
	log4cpp::Category &category;
	static std::map<Glib::ustring, bool> init;
	ConfigFile config;
};
}
#endif /* LOGGER_H_ */
