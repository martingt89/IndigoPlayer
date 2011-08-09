/*
 * ScriptGenerator.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "ScriptGenerator.h"

ScriptGenerator::ScriptGenerator(Glib::ustring path) {
	mplayerPath = path;
}

ScriptGenerator::~ScriptGenerator() {
	// TODO Auto-generated destructor stub
}

std::list<Glib::ustring> ScriptGenerator::generate(IndigoFile* file){
	std::list<Glib::ustring> empty;
	return empty;
}
