/*
 * ScriptGenerator.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "ScriptGenerator.h"

ScriptGenerator::ScriptGenerator() {
	controlPanel = NULL;
	videoBoard = NULL;
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
std::list<Glib::ustring> ScriptGenerator::generate(IndigoFile* file) {
	std::list<Glib::ustring> empty;
	empty.push_back(mplayerPath);

	if (controlPanel)
		getFromControlPanel(empty);

	if (videoBoard)
		getVideoBoard(empty);

	empty.push_back("-ass");

	getConfig(empty);


	empty.push_back("-vo");
	empty.push_back("gl");
	empty.push_back("-ao");
	empty.push_back("pulse");
	empty.push_back("-osdlevel");
	empty.push_back("0");

	empty.push_back("-slave");
	empty.push_back("-quiet");
	empty.push_back("-identify");
	empty.push_back(file->getFilePath());
	return empty;
}
void ScriptGenerator::getFromControlPanel(std::list<Glib::ustring> &parameters) {
	parameters.push_back("-volume");
	if(controlPanel->isMute())
		parameters.push_back("0");
	else
		parameters.push_back(Glib::ustring::format(controlPanel->getAudioLevel()));

}
void ScriptGenerator::getVideoBoard(std::list<Glib::ustring> &parameters) {
	parameters.push_back("-wid");
	parameters.push_back(Glib::ustring::format(videoBoard->getXID()));
}
void ScriptGenerator::getConfig(std::list<Glib::ustring> &parameters){
	Glib::ustring cp = config.getSubCp();
	if(cp.length() > 0){
		parameters.push_back("-subcp");
		parameters.push_back(cp);
//		std::cout<<"-subcp "<<cp<<std::endl;
	}
	cp = config.getSubColor();
	if(cp.length() > 0){
		parameters.push_back("-ass-color");
		parameters.push_back(cp);
//		std::cout<<"-ass-color"<<cp<<std::endl;
	}
}
