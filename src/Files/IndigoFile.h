/*
 * IndigoFile.h
 *
 *  Created on: 2.8.2011
 *      Author: xgeier
 */

#ifndef INDIGOFILE_H_
#define INDIGOFILE_H_

#include <list>
#include <glibmm/ustring.h>
#include <giomm/file.h>

class IndigoFile {
public:
	IndigoFile(Glib::ustring path, bool);
	IndigoFile();
	virtual ~IndigoFile();
	Glib::ustring getName();
	Glib::ustring getFilePath();
	bool getMenu();
	Glib::ustring getSoundFile();
	Glib::ustring getSubtitleFile();
	double getSubtitleFPS();
	int getSubtitleDelayms();
	int getSoundDelayms();
private:
	Glib::ustring filePath;
	bool menu;
	Glib::ustring soundFile;
	Glib::ustring subtitleFile;
	bool play;
	double subtitleFPS;
	int subtitleDelayms;
	int soundDelayms;
};

#endif /* INDIGOFILE_H_ */
