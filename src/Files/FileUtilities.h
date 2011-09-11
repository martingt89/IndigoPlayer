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
#include <sys/stat.h>
#include "IndigoFile.h"

class FileUtilities {
public:
	FileUtilities();
	virtual ~FileUtilities();
	std::list<Glib::ustring> fileToPlaylist(Glib::ustring file);
	std::list<IndigoFile*> stringListToFiles(std::list<Glib::ustring> files, bool folders, int depth=5);
	Glib::ustring fileToPath(Glib::ustring file);
	Glib::ustring getConfigFolder();
	bool createFolderSkeleton(Glib::ustring name, Glib::ustring log);
private:
	static std::map<Glib::ustring, IndigoFileType::FileType> types;
};

#endif /* FILEUTILITIES_H_ */
