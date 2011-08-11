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
#include "../../Settings.h"

class ScriptGenerator {
public:
	ScriptGenerator();
	virtual ~ScriptGenerator();
	std::list<Glib::ustring> generate(IndigoFile* file);
	void setVideoBoard(VideoBoard* board);
	void setControlPanel(ControlPanel* panel);
private:
	void getFromControlPanel(std::list<Glib::ustring> &parameters);
	void getVideoBoard(std::list<Glib::ustring> &parameters);
	ControlPanel* controlPanel;
	VideoBoard* videoBoard;
	Glib::ustring mplayerPath;
	int XID;
};

#endif /* SCRIPTGENERATOR_H_ */
