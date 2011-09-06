/*
 * MyComboBox.h
 *
 *  Created on: 14.8.2011
 *      Author: xgeier
 */

#ifndef MYCOMBOBOX_H_
#define MYCOMBOBOX_H_

#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodel.h>
#include <glibmm/ustring.h>
#include <string>

class MyComboBox {
private:
	class ModelColumns: public Gtk::TreeModel::ColumnRecord {
	public:

		ModelColumns() { add(colId); add(colText); add(doubleVlaue); add(textValue);}

	    Gtk::TreeModelColumn<int> colId;
	    Gtk::TreeModelColumn<double> doubleVlaue;
		Gtk::TreeModelColumn<Glib::ustring> colText;
		Gtk::TreeModelColumn<Glib::ustring> textValue;
	};
	ModelColumns columnsModel;
public:
	MyComboBox(Gtk::ComboBox* myBox);
	virtual ~MyComboBox();
	void pushBack(Glib::ustring, bool select = false);
	void pushBack(Glib::ustring text, int value, bool select = false);
	void pushBack(Glib::ustring text, double value, bool select = false);
	void clear();
//	void addNone();
	void addDefault(Glib::ustring text, int value=-1);
	double getDoubleValue();
	Glib::ustring getStringValue();
	int getOrder();
	void selectText(Glib::ustring text);
private:
	Glib::ustring convertText(Glib::ustring intpuText);
	Gtk::ComboBox* comboBox;
	Glib::RefPtr<Gtk::ListStore> refTreeModel;
	int number;
};

#endif /* MYCOMBOBOX_H_ */
