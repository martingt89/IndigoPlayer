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
}

void ScriptGenerator::setVideoBoard(VideoBoard* board) {
	videoBoard = board;
}
void ScriptGenerator::setControlPanel(ControlPanel* panel) {
	controlPanel = panel;
}
std::list<Glib::ustring> ScriptGenerator::generate(IndigoFile* file, bool loadTime, SavedFileInfo* info) {
	std::list<Glib::ustring> empty;
	if(config.isSet(IndigoConfig::MPLAYERPATH)){
		mplayerPath = config.getAsString(IndigoConfig::MPLAYERPATH);
	}else{
		return empty;
	}
	empty.push_back(mplayerPath);

	if (controlPanel)
		getFromControlPanel(empty);

	if (videoBoard)
		getVideoBoard(empty);

	if (info){
		getFromSavedInfo(empty, info, loadTime);
		getCollors(empty, info);
	}

	empty.push_back("-ass");

	getConfig(empty);

	empty.push_back("-vo");
	empty.push_back("gl");

	Glib::ustring device;
	if(config.get(IndigoConfig::AUDIOOUTPUT, device)){
		empty.push_back("-ao");
		empty.push_back(device);
	}

	empty.push_back("-nokeepaspect");

	empty.push_back("-af");
	empty.push_back("scaletempo");

	empty.push_back("-osdlevel");
	empty.push_back("0");
	empty.push_back("-slave");
	empty.push_back("-quiet");
	empty.push_back("-identify");
	if(file->getType() == IndigoFileType::DVD){
		empty.push_back("dvd://");
		empty.push_back("-dvd-device");
	}
	empty.push_back(file->getFilePath());

	return empty;
}
void ScriptGenerator::getCollors(std::list<Glib::ustring> &parameters, SavedFileInfo* info){
	double brig, cont, satur, hue, gamma;
	info->getCollors(&brig, &satur, &cont, &gamma, &hue);
	parameters.push_back("-brightness");
	parameters.push_back(Glib::ustring::format(brig));
	parameters.push_back("-contrast");
	parameters.push_back(Glib::ustring::format(cont));
	parameters.push_back("-hue");
	parameters.push_back(Glib::ustring::format(hue));
	parameters.push_back("-saturation");
	parameters.push_back(Glib::ustring::format(satur));
}
void ScriptGenerator::getFromSavedInfo(std::list<Glib::ustring> &parameters, SavedFileInfo* info,
		bool loadTime) {
	if (loadTime) {
		parameters.push_back("-ss");
		parameters.push_back(Glib::ustring::format(info->getAktualTime()));
	}
	if(info->getPlaySpeed() != 1){
		parameters.push_back("-speed");
		parameters.push_back(Glib::ustring::format(info->getPlaySpeed()));
	}
	if(info->getAktualChapter() != 1){
		parameters.push_back("-vid");
		parameters.push_back(Glib::ustring::format(info->getAktualChapter()));
	}
	if(info->getSoundPosition() != 0){
		parameters.push_back("-delay");
		parameters.push_back(Glib::ustring::format(info->getSoundPosition()));
	}
	if(info->getSubtitlePosition() != 0){
		parameters.push_back("-subdelay");
		parameters.push_back(Glib::ustring::format(info->getSubtitlePosition()));
	}
	{
		if (info->getSubPath().size() != 0) {
			parameters.push_back("-sub");
			parameters.push_back(info->getSubPath());
		}
		if (info->getAudioPath().size() != 0) {
			parameters.push_back("-audiofile");
			parameters.push_back(info->getAudioPath());
		}
	}
	int rot = 0;
	{
		switch (info->getRotate()) {
		case 90:
			parameters.push_back("-vf-add");
			parameters.push_back("rotate=1");
			rot = 1;
			break;
		case 180:
			parameters.push_back("-flip");
			break;
		case 270:
			parameters.push_back("-vf-add");
			parameters.push_back("rotate=2");
			rot = 1;
			break;
		default:
			break;
		}
	}
	{
		int w, h;
		int up, down, left, right;
		info->getResolution(&w, &h);
		if(w > 0 && h > 0){
			info->getCrop(&up, &down, &left, &right);
			int ud = up + down;
			int lr = left + right;
			parameters.push_back("-vf-add");
			if(rot == 0){
				parameters.push_back( "crop=" + Glib::ustring::format(w - lr) + ":" +
					Glib::ustring::format(h - ud) + ":" + Glib::ustring::format(left) +
					":" + Glib::ustring::format(up));
			}
			if(rot == 1){
				parameters.push_back( "crop=" + Glib::ustring::format(h - ud) + ":" +
						Glib::ustring::format(w - lr) + ":" + Glib::ustring::format(up) +
					":" + Glib::ustring::format(left));
			}
		}
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
	if (config.isSet(IndigoConfig::SUBCP)) {
		parameters.push_back("-subcp");
		parameters.push_back(config.getAsString(IndigoConfig::SUBCP));
	}

	if (config.isSet(IndigoConfig::SUBCOLOR)) {
		parameters.push_back("-ass-color");
		parameters.push_back(config.getAsString(IndigoConfig::SUBCOLOR));
	}
}
//-ass-border-color
//-ass-bottom-margin
//-noautosub
