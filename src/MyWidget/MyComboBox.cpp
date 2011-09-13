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
		if (row[columnsModel.textValue] == text) {
			find = true;
			break;
		}
		row++;
	}
	if (find == false) {

		row = *(refTreeModel->append());
		row[columnsModel.colText] = convertText(text);
		row[columnsModel.textValue] = text;
		//row[columnsModel.colText] = text;
		//row[columnsModel.textValue] = convertText(text);
		row[columnsModel.colId] = number;
		row[columnsModel.doubleVlaue] = value;
		number++;
	}
	if (select) {
		comboBox->set_active(*row);
	}
}
void MyComboBox::selectText(Glib::ustring text) {
	Gtk::TreeModel::Row row = *refTreeModel->children().begin();
	bool find = false;
	while (row) {
		if (row[columnsModel.textValue] == text) {
			find = true;
			break;
		}
		row++;
	}
	if (find)
		comboBox->set_active(*row);
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
		return row[columnsModel.textValue];
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
void MyComboBox::addDefault(Glib::ustring text, int value) {
	Gtk::TreeModel::Row row = *(refTreeModel->append());
	row[columnsModel.textValue] = text;
	row[columnsModel.colText] = text;
	row[columnsModel.colId] = value;
	comboBox->set_active(0);
}
Glib::ustring MyComboBox::convertText(Glib::ustring inputText) {
	int pos = inputText.find_last_of('/');
	Glib::ustring text = inputText;
	int max = 0;
	if ((pos >= 0) && (inputText.size() > (unsigned) pos)) {
		max = (inputText.size() - (pos + 1)) > 50 ?
				50 : (inputText.size() - (pos + 1));
		text = Glib::ustring(inputText, ++pos, max);
	}
	return text;
}
