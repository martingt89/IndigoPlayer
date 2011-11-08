/*
 * Options.cpp
 *
 *  Created on: 4.11.2011
 *      Author: martin89
 */

#include "Options.h"

Options::Options(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
Gtk::Window(cobject){

	builder->get_widget("SubEncodingOs", subEncodingCombo);			//Gtk::ComboBox
	builder->get_widget("SubColorEntryOs", subColorEntry); 			//Gtk::Entry
	builder->get_widget("SubBackEntryOs", subBackgroundEntry);		//Gtk::Entry
	builder->get_widget("SubSizeOs", subSizeCombo);					//Gtk::ComboBox
	builder->get_widget("SubColorOptions", subColorButton);			//Gtk::Button
	builder->get_widget("SubBackButtonOs1", subBackgroundButton);	//Gtk::Button
	builder->get_widget("StatusMessageOs", statusMessageLabel);		//Gtk::Label

	builder->get_widget("SaveOptions", saveButton);	//Gtk::Button
	builder->get_widget("CancelOptions", cancelButton);	//Gtk::Button

	mySubEncodingCombo = new MyComboBox(subEncodingCombo);
	mySubSizeCombo = new MyComboBox(subSizeCombo);
	initEncoding();
	initElements();
	saveButton->signal_clicked().connect(sigc::mem_fun(this, &Options::saveOptions));
	cancelButton->signal_clicked().connect(sigc::mem_fun(this, &Options::CancelOptions));
	this->signal_show ().connect(sigc::mem_fun(this, &Options::showWindow));
}

void Options::showWindow(){
	initValues();
}
void Options::saveOptions(){
	configFile.set(IndigoConfig::SUBCP, encoding[mySubEncodingCombo->getStringValue()]);
	configFile.saveToFile();
	this->hide();
}

void Options::CancelOptions(){
	this->hide();
}

void Options::initElements(){
	mySubSizeCombo->pushBack("Default", -1, true);
	for(int i = 2; i < 40; i = i+2){
		mySubSizeCombo->pushBack(Glib::ustring::format(i),i,false);
	}

	std::map<Glib::ustring, Glib::ustring>::iterator it;
	if((it = encoding.begin()) !=  encoding.end()){
		mySubEncodingCombo->pushBack(it->first, true);
	}
	for(it ; it != encoding.end(); it++){
		mySubEncodingCombo->pushBack(it->first,false);
	}

}
void Options::initValues(){	//read data from hashtable and add to graphic fields
	subColorEntry->set_text(configFile.getAsString(IndigoConfig::SUBCOLOR));
	std::map<Glib::ustring, Glib::ustring>::iterator it;

	for(it = encoding.begin(); it != encoding.end(); it++){
		if(it->second == configFile.getAsString(IndigoConfig::SUBCP))
		mySubEncodingCombo->selectText(it->first);
	}
}
Options::~Options() {
	delete subEncodingCombo;
	delete subColorEntry;
	delete subBackgroundEntry;
	delete subSizeCombo;
	delete subColorButton;
	delete subBackgroundButton;
	delete statusMessageLabel;
	delete saveButton;
	delete cancelButton;
	delete mySubEncodingCombo;
	delete mySubSizeCombo;
}
