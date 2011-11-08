/*
 * PathLoader.cpp
 *
 *  Created on: 13.9.2011
 *      Author: martin89
 */

#include "GraphicPathLoader.h"

Glib::ustring GraphicPathLoader::table[13];
bool GraphicPathLoader::init = false;

GraphicPathLoader::GraphicPathLoader() {
	if(!init){
		table[IndigoPath::GCONTROLPANEL] = GLADECONTROLPANEL;
		table[IndigoPath::GOPENDIALOG] = GLADEOPENDIALOG;
		table[IndigoPath::GPLAYERWINDOW] = GLADEPLAYERWINDOW;
		table[IndigoPath::GTHISOPTIONS] = GLADETHISOPTIONS;
		table[IndigoPath::GOPENWINDOW] = GLADEOPENWINDOW;

		table[IndigoPath::GOPTIONSWIN] = GLADEOPTIONSWINDOW;

		table[IndigoPath::PLAYIMAGE] = PLAYIMAGEGLADE;
		table[IndigoPath::PAUSEIMAG] = PAUSEIMAGEGLADE;
		table[IndigoPath::SOUNDIMAG] = SOUNDIMAGEGLADE;
		table[IndigoPath::MUTEIMAGE] = MUTEIMAGEGLADE;

		table[IndigoPath::BLANKARROWIMAGE] = BLANKARROW;
		table[IndigoPath::BLACKARROWIMAGE] = BLACKARROW;
		table[IndigoPath::LOGOIMAGE] = ICONIMAGE;
		init = true;
	}
}

Glib::ustring GraphicPathLoader::getPath(IndigoPath::Path path){
	Glib::ustring street = Glib::ustring(DATADIR)+"/"+Glib::ustring(DEFAULTINDIGOFOLDER)+table[path];
	if(Glib::file_test(street, Glib::FILE_TEST_EXISTS) == true){
		loger.log(IndigoLogger::DEBUG, "Loadding "+street);
		return street;
	}
	street = DEFAULTIMAGESFOLDER+table[path];
	if(Glib::file_test(street, Glib::FILE_TEST_EXISTS) == true){
		loger.log(IndigoLogger::DEBUG, "Loadding "+street);
		return street;
	}
	street = Glib::ustring(DATADIR)+"/"+Glib::ustring(DEFAULTINDIGOFOLDER)+table[path];
	loger.log(IndigoLogger::FATAL, "Cannot find file: "+street);

	return street;
}
GraphicPathLoader::~GraphicPathLoader(){

}
