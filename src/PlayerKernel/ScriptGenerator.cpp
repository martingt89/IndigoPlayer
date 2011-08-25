/*
 * ScriptGenerator.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "ScriptGenerator.h"
#include <iostream>

ScriptGenerator::ScriptGenerator() {
	controlPanel = NULL;
	videoBoard = NULL;
	videoFilters = NULL;
	mplayerPath = MPLAYER;
}

ScriptGenerator::~ScriptGenerator() {
	// TODO Auto-generated destructor stub
}
void ScriptGenerator::setVideoBoard(VideoBoard* board) {
	videoBoard = board;
}
void ScriptGenerator::setControlPanel(ControlPanel* panel) {
	controlPanel = panel;
}
void ScriptGenerator::setVideoFilters(VideoFilters* filters) {
	videoFilters = filters;
}
std::list<Glib::ustring> ScriptGenerator::generate(IndigoFile* file, bool load, SavedData data) {
	std::list<Glib::ustring> empty;
	empty.push_back(mplayerPath);

	if (controlPanel)
		getFromControlPanel(empty);

	if (videoBoard)
		getVideoBoard(empty);

	if (videoFilters)
		getFromVideoFilters(empty, load, data);

	if (load)
		getVideoSavedData(empty, data);

	empty.push_back("-ass");

	getConfig(empty);

//	empty.push_back("dvd://");

	empty.push_back("-vo");
	empty.push_back("gl");
	empty.push_back("-ao");
	empty.push_back("pulse");

	empty.push_back("-osdlevel");
	empty.push_back("0");
	empty.push_back("-slave");
	empty.push_back("-quiet");
	empty.push_back("-identify");
//	empty.push_back("-dvd-device");
	empty.push_back(file->getFilePath());
	std::list<Glib::ustring>::iterator it;
	for(it = empty.begin(); it != empty.end(); it++){
		std::cout<<*it<<" ";
	}
	std::cout<<std::endl;

	return empty;
}
void ScriptGenerator::getVideoSavedData(std::list<Glib::ustring> &parameters, SavedData data) {
	parameters.push_back("-ss");
	parameters.push_back(Glib::ustring::format(data.getPosition()));
	//
	if (data.getSubPath().size() != 0) {
		parameters.push_back("-sub");
		parameters.push_back(data.getSubPath());
	} else if (data.getSubID() != -1) {
		parameters.push_back("-sid");
		parameters.push_back(Glib::ustring::format(data.getSubID()));
	}
	if (data.getAudioPath().size() != 0) {
		parameters.push_back("-audiofile");
		parameters.push_back(data.getAudioPath());
	} else if (data.getSubID() > -1) {
		parameters.push_back("-aid");
		parameters.push_back(Glib::ustring::format(data.getAudioID()));
	}
}
void ScriptGenerator::getFromVideoFilters(std::list<Glib::ustring> &parameters, bool load, SavedData data) {
	if (videoFilters->getRotate() != 0) {
		switch (videoFilters->getRotate()) {
		case 90:
			parameters.push_back("-vf-add");
			parameters.push_back("rotate=1");
			break;
		case 180:
			parameters.push_back("-flip");
			break;
		case 270:
			parameters.push_back("-vf-add");
			parameters.push_back("rotate=2");
			break;
		default:
			break;
		}
	}
	if (load) {
		int x, y;
		int up, down, left, right;
		parameters.push_back("-vf-add");
		x = data.getX();
		y = data.getY();
		videoFilters->getResize(up, down, left, right);
		int ud = up + down;
		int lr = left + right;
		parameters.push_back(
				"crop=" + Glib::ustring::format(x - lr) + ":" + Glib::ustring::format(y - ud) + ":"
						+ Glib::ustring::format(left) + ":" + Glib::ustring::format(up));
	}
}
void ScriptGenerator::getFromControlPanel(std::list<Glib::ustring> &parameters) {
	parameters.push_back("-volume");
	if (controlPanel->isMute())
		parameters.push_back("0");
	else
		parameters.push_back(Glib::ustring::format(controlPanel->getAudioLevel()));
}
void ScriptGenerator::getVideoBoard(std::list<Glib::ustring> &parameters) {
	parameters.push_back("-wid");
	parameters.push_back(Glib::ustring::format(videoBoard->getXID()));
}
void ScriptGenerator::getConfig(std::list<Glib::ustring> &parameters) {
	Glib::ustring cp = config.getSubCp();

	if (cp.length() > 0) {
		parameters.push_back("-subcp");
		parameters.push_back(cp);
	}
	cp = config.getSubColor();
	if (cp.length() > 0) {
		parameters.push_back("-ass-color");
		parameters.push_back(cp);
	}
}
//-noautosub
//-audiofile XX
