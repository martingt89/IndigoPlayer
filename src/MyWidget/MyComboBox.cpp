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
void MyComboBox::pushBack(Glib::ustring text, bool select) {
	pushBack(text, 0.0, select);
}
void MyComboBox::pushBack(Glib::ustring text, int value, bool select) {
	pushBack(text, double(value), select);
}
void MyComboBox::pushBack(Glib::ustring text, double value, bool select) {
	Gtk::TreeModel::Row row = *refTreeModel->children().begin();
	bool find = false;
	while (row) {
		if (row[columnsModel.colText] == text) {
			find = true;
			break;
		}
		row++;
	}
	if (find == false) {
		row = *(refTreeModel->append());
		row[columnsModel.colText] = text;
		row[columnsModel.colId] = number;
		row[columnsModel.doubleVlaue] = value;
		number++;
	}
	if (select) {
		comboBox->set_active(*row);
	}
}

void MyComboBox::clear() {
	refTreeModel->clear();
	number = 0;
}
double MyComboBox::getDoubleValue() {
	Gtk::TreeModel::iterator iter = comboBox->get_active();
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		return row[columnsModel.doubleVlaue];
	}
	return 0;
}
Glib::ustring MyComboBox::getStringValue() {
	Gtk::TreeModel::iterator iter = comboBox->get_active();
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		return row[columnsModel.colText];
	}
	return "";
}
int MyComboBox::getOrder() {
	Gtk::TreeModel::iterator iter = comboBox->get_active();
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		return row[columnsModel.colId];
	}
	return -1;
}
void MyComboBox::addNone() {
	Gtk::TreeModel::Row row = *(refTreeModel->append());
	row[columnsModel.colText] = "None";
	row[columnsModel.colId] = -1;
	comboBox->set_active(0);
}
