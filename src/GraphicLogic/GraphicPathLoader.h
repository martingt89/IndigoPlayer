/*
 * PathLoader.h
 *
 *  Created on: 13.9.2011
 *      Author: martin89
 */

#ifndef GRAPHICPATHLOADER_H_
#define GRAPHICPATHLOADER_H_

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
	LOGOIMAGE = 11,
	GOPTIONSWIN = 12
};
}

class GraphicPathLoader {
public:
	GraphicPathLoader();
	~GraphicPathLoader();
	Glib::ustring getPath(IndigoPath::Path path);
	Glib::ustring getConfigFilePath();
	Glib::ustring getLockFilePath();
	Glib::ustring getInterProcesPipePath();
	Glib::ustring getMainFolder();
	Glib::ustring getLogFolder();
private:
	static Glib::ustring table[13];
	static bool init;
	IndigoLogger::Logger loger;
};

#endif /* GRAPHICPATHLOADER_H_ */
