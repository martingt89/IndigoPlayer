/*
 * ThisOptions.cpp
 *
 *  Created on: 14.8.2011
 *      Author: xgeier
 */

#include "ThisOptions.h"

ThisOptions::ThisOptions(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		videoSpeedAdj(2, 0, 4) {
	lastSpeed = 1;
	colors = NULL;
	videoFilter = NULL;
	refGlade->get_widget("ThisOptionsWindow", thisOptionsWindow);
	refGlade->get_widget("VideoSpeed", videoSpeed);

	refGlade->get_widget("rotateComboBox", rotate);
	refGlade->get_widget("LeftRight", leftRight);
	refGlade->get_widget("UpDown", upDown);
	refGlade->get_widget("UpSpin", upSpin);
	refGlade->get_widget("DownSpin", downSpin);
	refGlade->get_widget("LeftSpin", leftSpin);
	refGlade->get_widget("RightSpin", rightSpin);
	refGlade->get_widget("UseCropVideo", useCropVideo);

	refGlade->get_widget("BrightnessScale", brightness);
	refGlade->get_widget("ContrastScale", contrast);
	refGlade->get_widget("GammaScale", gamma);
	refGlade->get_widget("HueScale", hue);
	refGlade->get_widget("SaturationScale", saturation);

	myRotate = new MyComboBox(rotate);

	makrInit();

	videoSpeed->set_adjustment(videoSpeedAdj);
	videoSpeedAdj.signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::videoSpeedChanged));
	leftRight->signal_toggled().connect(sigc::mem_fun(this, &ThisOptions::leftRightClicked));
	upDown->signal_toggled().connect(sigc::mem_fun(this, &ThisOptions::upDownClicked));
	upSpin->signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::upSpinClicked));
	downSpin->signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::downSpinClicked));
	leftSpin->signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::leftSpinClicked));
	rightSpin->signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::rightSpinClicked));
	useCropVideo->signal_clicked().connect(sigc::mem_fun(this, &ThisOptions::cropVideoClicked));
	brightness->get_adjustment()->signal_value_changed().connect(
			sigc::mem_fun(this, &ThisOptions::brightnessChanged));
	contrast->get_adjustment()->signal_value_changed().connect(
			sigc::mem_fun(this, &ThisOptions::contrastChanged));
	gamma->get_adjustment()->signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::gammaChanged));
	hue->get_adjustment()->signal_value_changed().connect(sigc::mem_fun(this, &ThisOptions::hueChanged));
	saturation->get_adjustment()->signal_value_changed().connect(
			sigc::mem_fun(this, &ThisOptions::saturationChanged));
	rotate->signal_changed().connect(sigc::mem_fun(this, &ThisOptions::rotateChanged));
}
void ThisOptions::show() {
	thisOptionsWindow->show();
}
void ThisOptions::stopPlaying() {
	myRotate->clear();
	upSpin->set_sensitive(false);
	downSpin->set_sensitive(false);
	leftSpin->set_sensitive(false);
	rightSpin->set_sensitive(false);
	videoSpeed->set_sensitive(false);
	useCropVideo->set_sensitive(false);
	brightness->set_sensitive(false);
	contrast->set_sensitive(false);
	gamma->set_sensitive(false);
	hue->set_sensitive(false);
	leftRight->set_sensitive(false);
	upDown->set_sensitive(false);
	saturation->set_sensitive(false);
}
void ThisOptions::runPlaying() {
	myRotate->pushBack("0", 0, true);
	myRotate->pushBack("90", 90);
	myRotate->pushBack("180", 180);
	myRotate->pushBack("270", 270);
	upSpin->set_sensitive(true);
	downSpin->set_sensitive(true);
	leftSpin->set_sensitive(true);
	rightSpin->set_sensitive(true);
	videoSpeed->set_sensitive(true);
	useCropVideo->set_sensitive(true);
	brightness->set_sensitive(true);
	contrast->set_sensitive(true);
	gamma->set_sensitive(true);
	hue->set_sensitive(true);
	leftRight->set_sensitive(true);
	upDown->set_sensitive(true);
	saturation->set_sensitive(true);
}
void ThisOptions::setColorsPointer(ColorSetings* colors) {
	this->colors = colors;
}
void ThisOptions::setFiltersPointer(VideoFilters* filter) {
	videoFilter = filter;
}
void ThisOptions::makrInit() {
	videoSpeed->add_mark(0, Gtk::POS_LEFT, "0,25x");
	videoSpeed->add_mark(1, Gtk::POS_LEFT, "0,50x");
	videoSpeed->add_mark(2, Gtk::POS_LEFT, "1,00x");
	videoSpeed->add_mark(3, Gtk::POS_LEFT, "2,00x");
	videoSpeed->add_mark(4, Gtk::POS_LEFT, "4,00x");

	brightness->add_mark(0, Gtk::POS_LEFT, "0");
	contrast->add_mark(0, Gtk::POS_LEFT, "0");
	gamma->add_mark(0, Gtk::POS_LEFT, "0");
	hue->add_mark(0, Gtk::POS_LEFT, "0");
	saturation->add_mark(0, Gtk::POS_LEFT, "0");
}
void ThisOptions::cropVideoClicked() {
	if (videoFilter)
		videoFilter->apply();
}
void ThisOptions::rotateChanged() {
	if (videoFilter)
		videoFilter->setRotateFilter(myRotate->getDoubleValue());
}
void ThisOptions::upSpinClicked() {
	if (upDown->get_active())
		downSpin->set_value(upSpin->get_value());
	if (videoFilter)
		videoFilter->cropFilter(upSpin->get_value(), rightSpin->get_value(), downSpin->get_value(),
				leftSpin->get_value());
}
void ThisOptions::downSpinClicked() {
	if (videoFilter)
		videoFilter->cropFilter(upSpin->get_value(), rightSpin->get_value(), downSpin->get_value(),
				leftSpin->get_value());
}
void ThisOptions::leftSpinClicked() {
	if (leftRight->get_active())
		rightSpin->set_value(leftSpin->get_value());
	if (videoFilter)
		videoFilter->cropFilter(upSpin->get_value(), rightSpin->get_value(), downSpin->get_value(),
				leftSpin->get_value());
}
void ThisOptions::rightSpinClicked() {
	if (videoFilter)
		videoFilter->cropFilter(upSpin->get_value(), rightSpin->get_value(), downSpin->get_value(),
				leftSpin->get_value());
}
void ThisOptions::leftRightClicked() {
	if (leftRight->get_active()) {
		rightSpin->set_sensitive(false);
		rightSpin->set_value(leftSpin->get_value());
	} else
		rightSpin->set_sensitive(true);
}
void ThisOptions::upDownClicked() {
	if (upDown->get_active()) {
		downSpin->set_sensitive(false);
		downSpin->set_value(upSpin->get_value());
	} else
		downSpin->set_sensitive(true);
}
void ThisOptions::contrastChanged() {
	if (colors)
		colors->setContrast(contrast->get_adjustment()->get_value());
}
void ThisOptions::gammaChanged() {
	if (colors)
		colors->setGamma(gamma->get_adjustment()->get_value());
}
void ThisOptions::hueChanged() {
	if (colors)
		colors->setHue(hue->get_adjustment()->get_value());
}
void ThisOptions::saturationChanged() {
	if (colors)
		colors->setSaturation(saturation->get_adjustment()->get_value());
}
void ThisOptions::brightnessChanged() {
	if (colors)
		colors->setBrightness(brightness->get_adjustment()->get_value());
}
void ThisOptions::videoSpeedChanged() {
	unsigned int num = 1;
	for (int i = 0; i < (int) (videoSpeedAdj.get_value() + 0.5); i++) {
		num *= 2;
	}
	if (lastSpeed != (int) (videoSpeedAdj.get_value() + 0.5)) {
		lastSpeed = (int) (videoSpeedAdj.get_value() + 0.5);
	}
	videoSpeedAdj.set_value(lastSpeed);
	if (videoFilter)
		videoFilter->setPlaySpeed(0.25 * num);
}

ThisOptions::~ThisOptions() {
	// TODO Auto-generated destructor stub
}

