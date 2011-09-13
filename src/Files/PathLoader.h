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

#include "../Settings.h"
#include "../Files/Logger.h"

#ifndef DATADIR
#define DATADIR "ui"
#endif

namespace IndigoPath{
enum Path{
	GCONTROLPANEL = 0,
	GOPENDIALOG = 1,
	GPLAYERWINDOW = 2,
	GTHISOPTIONS = 3,
	GOPENWINDOW = 4,
	PLAYIMAGE = 5,
	PAUSEIMAG = 6,
	SOUNDIMAG = 7,
	MUTEIMAGE = 8,
	BLANKARROWIMAGE = 9,
	BLACKARROWIMAGE = 10,
	LOGOIMAGE = 11
};
}

class PathLoader {
public:
	PathLoader();
	virtual ~PathLoader();
	Glib::ustring getPath(IndigoPath::Path path);
private:
	static Glib::ustring table[12];
	static bool init;
	IndigoLogger::Logger loger;
};

#endif /* PATHLOADER_H_ */
