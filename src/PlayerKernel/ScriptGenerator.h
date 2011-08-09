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

class ScriptGenerator {
public:
	ScriptGenerator(Glib::ustring path);
	virtual ~ScriptGenerator();
	std::list<Glib::ustring> generate(IndigoFile* file);
private:
	Glib::ustring mplayerPath;
};

#endif /* SCRIPTGENERATOR_H_ */
