/*
 * FileUtilities.cpp
 *
 *  Created on: 3.8.2011
 *      Author: xgeier
 */

#include "FileUtilities.h"
#include <iostream>

std::map<Glib::ustring, IndigoFileType::FileType> FileUtilities::types;

FileUtilities::FileUtilities() {
	if(types.size() == 0){
		types[".iso"] = IndigoFileType::DVD;
		types[".flv"] = IndigoFileType::VIDEO;
		types[".mp3"] = IndigoFileType::AUDIO;
		types[".m3p"] = IndigoFileType::PLAYLIST;
		types[".ass"] = IndigoFileType::SUBTITLE;
		types[".aqt"] = IndigoFileType::SUBTITLE;
		types[".jss"] = IndigoFileType::SUBTITLE;
		types[".sub"] = IndigoFileType::SUBTITLE;
		types[".ttxt"] = IndigoFileType::SUBTITLE;
		types[".ssf"] = IndigoFileType::SUBTITLE;
		types[".srt"] = IndigoFileType::SUBTITLE;
		types[".ssa"] = IndigoFileType::SUBTITLE;
		types[".ass"] = IndigoFileType::SUBTITLE;
	}
}

FileUtilities::~FileUtilities() {
}

std::list<Glib::ustring> FileUtilities::fileToPlaylist(Glib::ustring filePath) {
	//if(file.isPlaylist){
	//	prekonvertuj playlist na subory
	//}
	std::list<Glib::ustring> files;
	if (!Glib::file_test(filePath, Glib::FILE_TEST_EXISTS)) {
		Glib::RefPtr<Gio::File> file = Gio::File::create_for_uri(filePath);
		if (file->get_path().length() != 0) {
			filePath = file->get_path();
		} else if (file->get_uri().length() != 0) {
			filePath = file->get_uri();
		}
	}
	files.push_back(filePath);

	return files;
}
Glib::ustring FileUtilities::fileToPath(Glib::ustring file) {
	Glib::ustring files = file;
	if (!Glib::file_test(file, Glib::FILE_TEST_EXISTS)) {
		Glib::RefPtr<Gio::File> filets = Gio::File::create_for_uri(file);
		if (filets->get_path().length() != 0) {
			files = filets->get_path();
		} else if (filets->get_uri().length() != 0) {
			files = filets->get_uri();
		}
	}
	return files;
}
std::list<IndigoFile*> FileUtilities::stringListToFiles(std::list<Glib::ustring> files, bool folders, int depth){
	std::list<Glib::ustring>::iterator it;
	Glib::ustring::size_type pos;
	IndigoFileType::FileType ift;
	std::list<IndigoFile*> fileList;
	if(depth < -1) return fileList;

	for(it = files.begin(); it != files.end(); it++){
		ift = IndigoFileType::UNKNOWN;
		pos = 0;
		pos = it->find_last_of(".");
		if(pos < it->size()){
			if(types.find(Glib::ustring(*it, pos)) != types.end())
				ift = types[Glib::ustring(*it, pos)];
		}
		if(ift == IndigoFileType::PLAYLIST){
			//prekonvertuj na list stringov, pusti rekurziu a margni s existujucim
		}else{
			Glib::ustring path = fileToPath(*it);
			if(Glib::file_test(path,  Glib::FILE_TEST_IS_DIR)){
				if(Glib::path_get_basename(path) == "VIDEO_TS"){
					fileList.push_back(new IndigoFile(path, IndigoFileType::DVD));
				}else
				if(folders){
					Glib::ustring child;
					Glib::Dir aktual(path);
					int ss = path.size();
					if(path.c_str()[ss] != '/')
						path+='/';
					std::list<Glib::ustring> ff;
					while((child = aktual.read_name()).size() != 0){
						ff.push_back(path+child);
					}
					std::list<IndigoFile*> newFiles = (stringListToFiles(ff, true, depth-1));
					fileList.merge(newFiles);
				}
			}else{
				fileList.push_back(new IndigoFile(path, ift));
			}
		}
	}
	return fileList;
}
Glib::ustring FileUtilities::getConfigFolder(){
	return Glib::get_user_config_dir () + "/";
}
bool FileUtilities::createFolderSkeleton(Glib::ustring name, Glib::ustring log){
	if(!Glib::file_test(getConfigFolder()+name, Glib::FILE_TEST_EXISTS)){
		if(mkdir ((getConfigFolder()+name).c_str(), 0700) < 0)
			return false;
	}else{
		if(!Glib::file_test(getConfigFolder()+name, Glib::FILE_TEST_IS_DIR)){
			return false;
		}
	}
	if(!Glib::file_test(getConfigFolder()+name+"/"+log, Glib::FILE_TEST_EXISTS)){
		if(mkdir ((getConfigFolder()+name+"/"+log).c_str(), 0700) < 0)
			return false;
	}else{
		if(!Glib::file_test(getConfigFolder()+name+"/"+log, Glib::FILE_TEST_IS_DIR)){
			return false;
		}
	}

	return true;
}
