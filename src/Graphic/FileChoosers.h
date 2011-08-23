/*
 * FileChoosers.h
 *
 *  Created on: 22.8.2011
 *      Author: xgeier
 */

#ifndef FILECHOOSERS_H_
#define FILECHOOSERS_H_
#include <gtkmm/filechooserdialog.h>
#include <glibmm/ustring.h>
#include <gtkmm/stock.h>
class FileChoosers {
public:
	FileChoosers();
	virtual ~FileChoosers();
	Glib::ustring getSubtitleFile();
private:
	 Gtk::FileChooserDialog* fileOpen;
};

#endif /* FILECHOOSERS_H_ */
