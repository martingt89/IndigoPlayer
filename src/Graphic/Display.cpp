/*
 * Display.cpp
 *
 *  Created on: 10.8.2011
 *      Author: xgeier
 */

#include "Display.h"

#include <iostream>

IDisplay::IDisplay(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::DrawingArea(cobject) {
	std::cout<<GDK_WINDOW_XID(Glib::unwrap(this->get_window()));
	std::cout<<"nieco"<<std::endl;
	this->set_double_buffered(false);
}

IDisplay::~IDisplay() {
	// TODO Auto-generated destructor stub
}
int xx = 0;
void IDisplay::on_realize(){
	std::cout<<"realize "<<xx++<<std::endl;
}
void IDisplay::on_state_changed(enum Gtk::StateType state){
	std::cout<<"state "<<xx++<<std::endl;
}
bool IDisplay::on_expose_event(GdkEventExpose* event){
	std::cout<<"expose "<<xx++<<std::endl;
	std::cout<<"x "<<this->get_width()<<" y "<<this->get_height()<<std::endl;
	return true;
}
