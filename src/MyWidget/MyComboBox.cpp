/*
 * MyComboBox.cpp
 *
 *  Created on: 14.8.2011
 *      Author: xgeier
 */

#include "MyComboBox.h"

MyComboBox::MyComboBox(Gtk::ComboBox* myBox) {
	comboBox = myBox;
	refTreeModel = Gtk::ListStore::create(columnsModel);
	comboBox->set_model(refTreeModel);
	comboBox->pack_start(columnsModel.colText);
	number = 0;
}

MyComboBox::~MyComboBox() {
	// TODO Auto-generated destructor stub
}
void MyComboBox::pushBack(Glib::ustring text){
	pushBack(text, 0);
}
void MyComboBox::pushBack(Glib::ustring text, double value){
	Gtk::TreeModel::Row row = *(refTreeModel->append());
	row[columnsModel.colText] = text;
	row[columnsModel.colId] = number;
	row[columnsModel.doubleVlaue] = value;
	if(number == 0)
		comboBox->set_active(0);
	number++;
}

void MyComboBox::clear(){
	refTreeModel->clear();
	number = 0;
}
double MyComboBox::getDoubleValue(){
	Gtk::TreeModel::iterator iter = comboBox->get_active();
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  return row[columnsModel.doubleVlaue];
	}
	return 0;
}
Glib::ustring MyComboBox::getStringValue(){
	Gtk::TreeModel::iterator iter = comboBox->get_active();
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  return row[columnsModel.colText];
	}
	return "";
}
int MyComboBox::getOrder(){
	Gtk::TreeModel::iterator iter = comboBox->get_active();
		if(iter)
		{
		  Gtk::TreeModel::Row row = *iter;
		  return row[columnsModel.colId];
		}
		return -1;
}
void MyComboBox::addNone(){
	Gtk::TreeModel::Row row = *(refTreeModel->append());
	row[columnsModel.colText] = "None";
	row[columnsModel.colId] = -1;
	comboBox->set_active(0);
}
