/*
 * GraphicData.h
 *
 *  Created on: 2.9.2011
 *      Author: xgeier
 */

#ifndef GRAPHICDATA_H_
#define GRAPHICDATA_H_

#include <list>
#include <glibmm/ustring.h>

class GraphicData {
public:
	GraphicData();
	void setStart(bool start);
	void setEnd(bool end);
	void setAktualTime(int time);
	void setLength(int length);
	void setSubtitleList(std::list<Glib::ustring> subtitle);
	void setAudioList(std::list<Glib::ustring> audio);
	void setResolution(int width, int height);
	bool getStart();
	bool getEnd();
	int getAktualTime();
	int getLenght();
	void getResolution(int *width, int* height);
	std::list<Glib::ustring> getSubtitleList();
	std::list<Glib::ustring> getAudioList();
	//
	bool isStart();
	bool isEnd();
	bool isAktualTime();
	bool isLenght();
	bool isResolution();
	bool isSubtitle();
	bool isAudio();
private:
	bool start;
	bool end;
	int aktualTime;
	int duration;
	int width;
	int height;
	std::list<Glib::ustring> subtitle;
	std::list<Glib::ustring> audio;
	//
	bool wasStart;
	bool wasEnd;
	bool wasAktualTime;
	bool wasDuration;
	bool wasResolution;
	bool wasSubtitle;
	bool wasAudio;
};

#endif /* GRAPHICDATA_H_ */
