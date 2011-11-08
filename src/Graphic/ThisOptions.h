/*
 * ThisOptions.h
 *
 *  Created on: 14.8.2011
 *      Author: xgeier
 */

#ifndef THISOPTIONS_H_
#define THISOPTIONS_H_

#include <gtkmm/scale.h>
#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/combobox.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include "../MyWidget/MyComboBox.h"
#include "../PlayerKernel/MplayerInterface.h"
#include "../Player/ColorSetings.h"
#include "../Interfaces/VideoFilters.h"

class ThisOptions {
public:
	ThisOptions(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ThisOptions();
	void show();
	void setColorsPointer(ColorSetings* colors);
	void setFiltersPointer(VideoFilters* filter);
	void stopPlaying();
	void runPlaying();
private:
	void closeThisOpt();
	void rotateChanged();
	void leftRightClicked();
	void upDownClicked();
	void upSpinClicked();
	void downSpinClicked();
	void leftSpinClicked();
	void rightSpinClicked();
	void cropVideoClicked();
	void contrastChanged();
	void gammaChanged();
	void hueChanged();
	void saturationChanged();
	void brightnessChanged();
	void videoSpeedChanged();
	void makrInit();
	Gtk::Window* thisOptionsWindow;
	Gtk::HScale* videoSpeed;

	Gtk::Button* thisOptCloseBut;

	Gtk::ComboBox* rotate;
	MyComboBox* myRotate;
	Gtk::CheckButton* leftRight;
	Gtk::CheckButton* upDown;
	Gtk::SpinButton* upSpin;
	Gtk::SpinButton* downSpin;
	Gtk::SpinButton* leftSpin;
	Gtk::SpinButton* rightSpin;
	Gtk::Button* useCropVideo;
//--------------------------------------------------
	Gtk::Scale* brightness;
	Gtk::Scale* contrast;
	Gtk::Scale* gamma;
	Gtk::Scale* hue;
	Gtk::Scale* saturation;
//--------------------------------------------------
	Gtk::Adjustment videoSpeedAdj;
	int lastSpeed;

	VideoFilters* videoFilter;
	ColorSetings* colors;
};

#endif /* THISOPTIONS_H_ */
