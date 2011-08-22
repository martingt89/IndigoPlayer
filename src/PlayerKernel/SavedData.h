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
	void setSubtitle(Glib::ustring path);
	Glib::ustring getSubPath();
private:
	int resX;
	int resY;
	int position;
	Glib::ustring subPath;
};

#endif /* SAVEDDATA_H_ */
