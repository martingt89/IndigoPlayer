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

namespace IndigoFileType{
	enum FileType { VIDEO, AUDIO, SUBTITLE, URL, UNKNOWN, PLAYLIST, DVD };
};

class IndigoFile {
public:
	IndigoFile(Glib::ustring path , IndigoFileType::FileType type);
	IndigoFile();
	virtual ~IndigoFile();
	void init();
	Glib::ustring getName();
	Glib::ustring getFilePath();
	bool getMenu();
	Glib::ustring getSoundFile();
	Glib::ustring getSubtitleFile();
	double getSubtitleFPS();
	int getSubtitleDelayms();
	int getSoundDelayms();
	IndigoFileType::FileType getType();
	//===================================
	void setMenu(bool menu);
	void setSoundFile(Glib::ustring sound);
	void setSubtitleFile(Glib::ustring subtitle);
	void setSubtitleFPS(double fps);
	void setSubtitleDelayms(int delay);
	void setSoundDelayms(int delay);
private:
	Glib::ustring filePath;
	bool menu;
	Glib::ustring soundFile;
	Glib::ustring subtitleFile;
	bool play;
	double subtitleFPS;
	int subtitleDelayms;
	int soundDelayms;
	IndigoFileType::FileType type;
};

#endif /* INDIGOFILE_H_ */
