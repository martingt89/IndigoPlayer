/*
 * ScriptGenerator.h
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#ifndef SCRIPTGENERATOR_H_
#define SCRIPTGENERATOR_H_

#include <glibmm/ustring.h>
#include <list>
#include "SavedData.h"
#include "VideoFilters.h"
#include "../Files/IndigoFile.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/ControlPanel.h"
#include "../Files/ConfigFile.h"
#include "../../Settings.h"

class ScriptGenerator {
public:
	ScriptGenerator();
	virtual ~ScriptGenerator();
	std::list<Glib::ustring> generate(IndigoFile* file, bool load, SavedData data);
	void setVideoBoard(VideoBoard* board);
	void setControlPanel(ControlPanel* panel);
	void setVideoFilters(VideoFilters* filters);
private:
	void getFromControlPanel(std::list<Glib::ustring> &parameters);
	void getFromVideoFilters(std::list<Glib::ustring> &parameters, bool load, SavedData data);
	void getVideoBoard(std::list<Glib::ustring> &parameters);
	void getConfig(std::list<Glib::ustring> &parameters);
	ControlPanel* controlPanel;
	VideoBoard* videoBoard;
	VideoFilters* videoFilters;
	ConfigFile config;
	Glib::ustring mplayerPath;
	int XID;
};

#endif /* SCRIPTGENERATOR_H_ */
