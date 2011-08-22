/*
 * FileUtilities.h
 *
 *  Created on: 3.8.2011
 *      Author: xgeier
 */

#ifndef FILEUTILITIES_H_
#define FILEUTILITIES_H_

#include <list>
#include <map>
#include <glibmm/ustring.h>
#include "IndigoFile.h"

class FileUtilities {
public:
	FileUtilities();
	virtual ~FileUtilities();
	void fileWalk(std::list<Glib::ustring> &list, int depth);
	std::list<Glib::ustring> fileToPlaylist(Glib::ustring file);
	std::list<IndigoFile*> stringListToFiles(std::list<Glib::ustring> files, bool folders, int depth=5);
	Glib::ustring fileToPath(Glib::ustring file);
private:
	static std::map<Glib::ustring, IndigoFileType::FileType> types;
};

#endif /* FILEUTILITIES_H_ */
