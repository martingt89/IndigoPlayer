/*
 * Display.h
 *
 *  Created on: 10.8.2011
 *      Author: xgeier
 */

#ifndef IDISPLAY_H_
#define IDISPLAY_H_

#include <gtkmm/drawingarea.h>
#include <gtkmm.h>
#include <gdk/gdkx.h>


class IDisplay : public Gtk::DrawingArea{
public:
	IDisplay(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~IDisplay();
	void on_realize();
	void on_state_changed(enum Gtk::StateType state);
	bool on_expose_event(GdkEventExpose* event);
};

#endif /* IDISPLAY_H_ */
