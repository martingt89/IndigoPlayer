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
#include "../Files/IndigoFile.h"
#include "../Graphic/VideoBoard.h"
#include "../Graphic/ControlPanel.h"
#include "../ConfigFile.h"
#include "../Player/SavedFileInfo.h"
#include "../Settings.h"

class ScriptGenerator {
public:
	ScriptGenerator();
	std::list<Glib::ustring> generate(IndigoFile* file, bool loadTime = false, SavedFileInfo* info=NULL);
	void setVideoBoard(VideoBoard* board);
	void setControlPanel(ControlPanel* panel);
private:
	void getCollors(std::list<Glib::ustring> &parameters, SavedFileInfo* info);
	void getFromSavedInfo(std::list<Glib::ustring> &parameters, SavedFileInfo* info, bool loadTime);
	void getFromControlPanel(std::list<Glib::ustring> &parameters);
	void getVideoBoard(std::list<Glib::ustring> &parameters);
	void getConfig(std::list<Glib::ustring> &parameters);
	void printScript(std::list<Glib::ustring> &parameters);
	ControlPanel* controlPanel;
	VideoBoard* videoBoard;
	ConfigFile config;
	Glib::ustring mplayerPath;
	int XID;
};

#endif /* SCRIPTGENERATOR_H_ */
