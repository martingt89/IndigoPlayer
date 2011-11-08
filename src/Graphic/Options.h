/*
 * Options.h
 *
 *  Created on: 4.11.2011
 *      Author: martin89
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <gtkmm/button.h>
#include <gtkmm/combobox.h>
#include <gtkmm/entry.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include "../ConfigFile.h"
#include "../MyWidget/MyComboBox.h"

class Options : public Gtk::Window{
public:
	Options(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~Options();
	void initElements();
	void initValues();
	void initEncoding(){
		encoding["Default"] = "";

		encoding["ISO 8859-1 Western Europe"] = "ISO_8859-1";
		encoding["ISO 8859-2 Western and Central Europe"] = "ISO_8859-2";
		encoding["ISO 8859-3 Western Europe and South European"] = "ISO_8859-3";
		encoding["ISO 8859-4 Western Europe and Baltic countries"] = "ISO_8859-4";
		encoding["ISO 8859-5 Cyrillic alphabet"] = "ISO_8859-5";
		encoding["ISO 8859-6 Arabic"] = "ISO_8859-6";
		encoding["ISO 8859-7 Greek"] = "ISO_8859-7";
		encoding["ISO 8859-8 Hebrew"] = "ISO_8859-8";
		encoding["ISO 8859-9 Western Europe"] = "ISO_8859-9";
		encoding["ISO 8859-14 Celtic languages"] = "ISO_8859-14";
		encoding["ISO 8859-15 Added the Euro sign"] = "ISO_8859-15";
		encoding["ISO 8859-16 Central"] = "ISO_8859-16";

		encoding["Windows-1250 for Central European languages"] = "Windows-1250";
		encoding["Windows-1251 for Cyrillic alphabets"] = "Windows-1251";
		encoding["Windows-1252 for Western languages"] = "Windows-1252";
		encoding["Windows-1253 for Greek"] = "Windows-1253";
		encoding["Windows-1254 for Turkish"] = "Windows-1254";
		encoding["Windows-1255 for Hebrew"] = "Windows-1255";
		encoding["Windows-1256 for Arabic"] = "Windows-1256";
		encoding["Windows-1257 for Baltic languages"] = "Windows-1257";
		encoding["Windows-1258 for Vietnamese"] = "Windows-1258";
		encoding["EUC-JP for Japan"] = "EUC-JP";
		encoding["ISO-2022-JP for Japan"] = "EUC-JP";

		encoding["UTF-7"] = "UTF-7";
		encoding["UTF-8"] = "UTF-8";
		encoding["UTF-16"] = "UTF-16";
		encoding["UTF-16BE 16-bit Big Endian"] = "UTF-16BE";
		encoding["UTF-16BL 16-bit Little Endian"] = "UTF-16LE";
		encoding["UTF-32"] = "UTF-32";
		encoding["UTF-32BE 32-bit Big Endian"] = "UTF-32BE";
		encoding["UTF-32BL 32-bit Little Endian"] = "UTF-32LE";

	};
private:
	ConfigFile configFile;
	Gtk::Button *subColorButton;
	Gtk::Button *subBackgroundButton;
	Gtk::Button *saveButton;
	Gtk::Button *cancelButton;

	Gtk::Entry *subBackgroundEntry;
	Gtk::Entry *subColorEntry;
	Gtk::ComboBox *subEncodingCombo;
	Gtk::ComboBox *subSizeCombo;
	Gtk::Label *statusMessageLabel;

	MyComboBox* mySubEncodingCombo;
	MyComboBox* mySubSizeCombo;
	std::map<Glib::ustring, Glib::ustring> encoding;
	//
	void saveOptions();
	void CancelOptions();
	void showWindow();
};

#endif /* OPTIONS_H_ */
