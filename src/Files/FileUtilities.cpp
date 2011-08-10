/*
 * FileUtilities.cpp
 *
 *  Created on: 3.8.2011
 *      Author: xgeier
 */

#include "FileUtilities.h"
#include <iostream>

FileUtilities::FileUtilities() {
	// TODO Auto-generated constructor stub
}

FileUtilities::~FileUtilities() {
	// TODO Auto-generated destructor stub
}

void FileUtilities::fileWalk(std::list<Glib::ustring> &list, int depth) {

}
std::list<Glib::ustring> FileUtilities::fileToPlaylist(Glib::ustring filePath) {
	//if(file.isPlaylist){
	//	prekonvertuj playlist na subory
	//}
	std::cout<<"FileUtilities"<<filePath<<std::endl;
	std::list<Glib::ustring> files;
	if (!Glib::file_test(filePath, Glib::FILE_TEST_EXISTS)) {
		Glib::RefPtr<Gio::File> file = Gio::File::create_for_uri(filePath);
		if (file->get_path().length() != 0) {
			filePath = file->get_path();
		} else if (file->get_uri().length() != 0) {
			filePath = file->get_uri();
		}
	}
	std::cout<<"FileUtilities push back"<<filePath<<std::endl;
	files.push_back(filePath);

	return files;
}
