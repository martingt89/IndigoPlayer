/*
 * ThisOptionsLoad.cpp
 *
 *  Created on: 22.8.2011
 *      Author: xgeier
 */

#include "ThisOptionsLoad.h"
#include <iostream>

ThisOptionsLoad::ThisOptionsLoad(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	playerSignal = NULL;
	refGlade->get_widget("AudioLoad", audioLoad);
	refGlade->get_widget("SubtitleLoad", subtitleLoad);
	refGlade->get_widget("AudioDelay", audioDelay);
	refGlade->get_widget("SubtitleDelay", subtitleDelay);
	refGlade->get_widget("VideoStream", videoStream);
	refGlade->get_widget("AudioStream", audioStream);
	refGlade->get_widget("SubtitleStream", subtitleStream);

	myVideoStream = new MyComboBox(videoStream);
	myAudioStream = new MyComboBox(audioStream);
	mySubtitleStream = new MyComboBox(subtitleStream);

	subtitleStream->signal_changed().connect(sigc::mem_fun(this, &ThisOptionsLoad::subStraemChanged));
	subtitleLoad->signal_clicked().connect(sigc::mem_fun(this, &ThisOptionsLoad::subButtonClicked));
	audioLoad->signal_clicked().connect(sigc::mem_fun(this, &ThisOptionsLoad::audButtonClicked));
	audioStream->signal_changed().connect(sigc::mem_fun(this, &ThisOptionsLoad::audStraemChanged));
}

ThisOptionsLoad::~ThisOptionsLoad() {
	// TODO Auto-generated destructor stub
}
void ThisOptionsLoad::audButtonClicked(){
	FileChoosers fs;
	Glib::ustring path = fs.getSoundFile();
	if(path.size() == 0) return;
	myAudioStream->pushBack(path, true);
}
void ThisOptionsLoad::audStraemChanged(){
//	std::cout<<"void ThisOptionsLoad::audStraemChanged()"<<std::endl;
	playerSignal->playAudio(myAudioStream->getStringValue());
}
void ThisOptionsLoad::subButtonClicked(){
	FileChoosers fs;
	Glib::ustring path = fs.getSubtitleFile();
	if(path.size() == 0) return;
	if(playerSignal)
		playerSignal->addSubtitle(path);
}
void ThisOptionsLoad::subStraemChanged(){
	if(mySubtitleStream->getOrder() == -1){
		if(playerSignal)
			playerSignal->playSubtitles("");
	}else{
		playerSignal->playSubtitles(mySubtitleStream->getStringValue());
	}
}
void ThisOptionsLoad::addSubtitles(Glib::ustring path, bool play){
	mySubtitleStream->pushBack(path, play);
}
void ThisOptionsLoad::setListener(PlayerSignals *sig){
	playerSignal = sig;
}
void ThisOptionsLoad::runPlaying(){
	mySubtitleStream->addDefault("None");
	audioLoad->set_sensitive(true);
	subtitleLoad->set_sensitive(true);
}
void ThisOptionsLoad::stopPlaying(){
	mySubtitleStream->clear();
	myAudioStream->clear();
	audioLoad->set_sensitive(false);
	subtitleLoad->set_sensitive(false);
}
void ThisOptionsLoad::addSubtitleList(std::list<Glib::ustring> files, bool firstShow){
	if(files.size() == 0) return;
	std::list<Glib::ustring>::iterator it = files.begin();
	if(firstShow){
		mySubtitleStream->pushBack(*it, true);
		it++;
	}
	for(; it != files.end(); it++){
		mySubtitleStream->pushBack(*it, false);
	}
}
void ThisOptionsLoad::addAudioList(std::list<Glib::ustring> files, bool firstShow){
	if(files.size() == 0) return;
	std::list<Glib::ustring>::iterator it = files.begin();
	if(firstShow){
		myAudioStream->pushBack(*it, true);
		it++;
	}
	for(; it != files.end(); it++){
		myAudioStream->pushBack(*it, false);
	}
}
