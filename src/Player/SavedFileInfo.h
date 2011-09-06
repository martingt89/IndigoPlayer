/*
 * SavedFileInfo.h
 *
 *  Created on: 1.9.2011
 *      Author: xgeier
 */

#ifndef SAVEDFILEINFO_H_
#define SAVEDFILEINFO_H_

#include <glibmm/ustring.h>

class SavedFileInfo {
public:
	SavedFileInfo();
	void clear();
	//==================
	void pause();
	void setAktulaTime(int time);
	void setCrop(int up, int down, int left, int right);
	void setSubtitlePosition(double pos);
	void setSoundPosition(double pos);
	void setPlaySpeed(double speed);
	void setRotate(int rotate);
	void setResolution(int width, int height);
	//==================
	void setSubtitlePath(Glib::ustring path);
	void setSubtitleID(int id);
	void setAudioPath(Glib::ustring path);
	void setAudioID(int id);
	//==================
	void setNumberOfChapters(int number);
	void setAktualChapter(int chapter);
	//==================
	bool getPause();
	int getAktualTime();
	void getCrop(int *up, int *down, int* left, int* right);
	double getSubtitlePosition();
	double getSoundPosition();
	double getPlaySpeed();
	int getRotate();
	void getResolution(int *width, int *height);
	//==================
	int getSubID();
	Glib::ustring getSubPath();
	int getAudioID();
	Glib::ustring getAudioPath();
	//==================
	int getNumberOfChapter();
	int getAktualChapter();
private:
	bool pp;
	int width;
	int height;
	//==================
	int aktualTime;
	double subtitlePosition;
	double soundPosition;
	//==================
	int cropUP;
	int cropDown;
	int cropLeft;
	int cropRight;
	//==================
	double playSpeed;
	int rotate;
	//==================
	Glib::ustring subPath;
	Glib::ustring audioPath;
	int subID;
	int audioID;
	//==================
	int numberChapters;
	int aktualChapter;
};

#endif /* SAVEDFILEINFO_H_ */
