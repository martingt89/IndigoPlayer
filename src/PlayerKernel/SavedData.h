/*
 * SavedData.h
 *
 *  Created on: 16.8.2011
 *      Author: xgeier
 */

#ifndef SAVEDDATA_H_
#define SAVEDDATA_H_

#include <glibmm/ustring.h>

class SavedData {
public:
	SavedData();
	virtual ~SavedData();
	void setResolution(int x, int y);
	void setPosition(double position);
	int getX();
	int getY();
	double getPosition();
	//::::::::::::::::::::::::::::::::::::::::::
	void setSubtitlePath(Glib::ustring path);
	void setSubtitleID(int id);
	void setAudioPath(Glib::ustring path);
	void setAudioID(int id);
	//::::::::::::::::::::::::::::::::::::::::::
	int getSubID();
	Glib::ustring getSubPath();
	int getAudioID();
	Glib::ustring getAudioPath();
	//::::::::::::::::::::::::::::::::::::::::::
private:
	int resX;
	int resY;
	int position;
	Glib::ustring subPath;
	Glib::ustring audioPath;
	int subID;
	int audioID;
};

#endif /* SAVEDDATA_H_ */
