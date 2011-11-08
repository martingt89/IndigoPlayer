/*
 * PathLoader.h
 *
 *  Created on: 13.9.2011
 *      Author: martin89
 */

#ifndef PATHLOADER_H_
#define PATHLOADER_H_

#include <glibmm/ustring.h>
#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h>

#include "../Settings.h"

class PathLoader {
public:
	Glib::ustring getConfigFilePath();
	Glib::ustring getLockFilePath();
	Glib::ustring getInterProcesPipePath();
	Glib::ustring getMainFolder();
	Glib::ustring getLogFolder();
	Glib::ustring getIProcessMQueueName();
};

#endif /* PATHLOADER_H_ */
