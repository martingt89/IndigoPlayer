/*
 * PathLoader.cpp
 *
 *  Created on: 13.9.2011
 *      Author: martin89
 */

#include "PathLoader.h"

Glib::ustring PathLoader::getConfigFilePath(){
	return getMainFolder() +CONFIG;
}
Glib::ustring PathLoader::getLockFilePath(){
	return getMainFolder()+ONEINSTANCELOCK;
}
Glib::ustring PathLoader::getInterProcesPipePath(){
	return getMainFolder()+ONEINSTANCEPIPE;
}
Glib::ustring PathLoader::getLogFolder(){
	return getMainFolder()+LOGFOLDER+"/";
}
Glib::ustring PathLoader::getMainFolder(){
	return Glib::get_user_config_dir () + "/" + INDIGONAME+"/";
}
Glib::ustring PathLoader::getIProcessMQueueName(){
	return "/"+Glib::ustring::format(INDIGONAME)+Glib::ustring::format(INDIGOVERSION);
}
