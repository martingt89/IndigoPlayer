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

class ThisOptions {
public:
	ThisOptions(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ThisOptions();
	void show();
	void setPlayerInt(MplayerInterface* interface);
	void addSubtitles(Glib::ustring, bool play);
private:
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
	Gtk::Button* audioLoad;
	Gtk::Button* subtitleLoad;
	Gtk::SpinButton* audioDelay;
	Gtk::SpinButton* subtitleDelay;
	Gtk::ComboBox* videoStream;
	Gtk::ComboBox* audioStream;
	Gtk::ComboBox* subtitleStream;

	MyComboBox* myVideoStream;
	MyComboBox* myAudioStream;
	MyComboBox* mySubtitleStream;

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

	MplayerInterface* mplayerInterface;
};

#endif /* THISOPTIONS_H_ */
