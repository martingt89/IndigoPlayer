/*
 * VideoBoard.cpp
 *
 *  Created on: 1.8.2011
 *      Author: xgeier
 */

#include "VideoBoard.h"

VideoBoard::VideoBoard(const Glib::RefPtr<Gtk::Builder>& builder) {
	boardSizeX = 0;
	boardSizeY = 0;
	showText = true;
	builder->get_widget("videoBoardDrawindBase", videoBoard);
	Gdk::Color black;
	Glib::RefPtr<Gdk::Window> win = videoBoard->get_window();
	win->set_background(black);
	win->clear();
	videoBoard->signal_expose_event().connect(
			sigc::mem_fun(this, &VideoBoard::on_expose_event));
	image = Gdk::Pixbuf::create_from_file("myimage.svg");
	imgX = image->get_width();
	imgY = image->get_height();
}

VideoBoard::~VideoBoard() {
	delete videoBoard;
}

//void VideoBoard::on_drop_files(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
//		const Gtk::SelectionData& selection_data, guint info, guint time) {
//
//	const int length = selection_data.get_length();
//	if ((length >= 0) && (selection_data.get_format() == 8)) {
//
//	//	std::cout << "Received \"" << selection_data.get_data_as_string()
//	//			<< "\" in label " << std::endl;
//		std::vector<Glib::ustring> file_list;
//
//		file_list = selection_data.get_uris();
//		std::list<Glib::ustring> uris;
//		for(unsigned int i = 0; i < file_list.size(); i++){
//			uris.push_back(file_list[i]);
//		}
//		if(file_list.size() > 0 && signals != 0)
//			signals->addFiles(uris, true, true);
//		 //if (file_list.size() > 0)
//	//	 {
//		// Glib::ustring path = Glib::filename_from_uri(file_list[0]);
//	//	 Glib::filename_from_utf8(file_list[0]);
//		 //std::cout<<Glib::file_test (path, Glib::FILE_TEST_EXISTS)<<std::endl;
//			// static Glib::RefPtr< Gio::File > file = Gio::File::create_for_uri (file_list[0]);
//	//		 static Glib::RefPtr< Gio::File > file = Gio::File::create_for_uri ("/home/xgeier/.gvfs/hd filmy na 127.0.0.1/9 2009 (1080p)/9 2009 (1080p).mkv");
//	//		 std::cout<<file->get_path()<<std::endl;
//	//	 }
//
//		//std::cout<<Glib::filename_from_uri(selection_data.get_data_as_string())<<std::endl;
//		//std::cout<<"targer: "<<selection_data.<<std::endl;
//	}
//
//	context->drag_finish(false, false, time);
//}
void VideoBoard::showPlay(bool show) {
	showText = show;
}

bool VideoBoard::on_timeout() {
	videoBoard->get_window()->clear();
	int x = videoBoard->get_window()->get_width();
	int y = videoBoard->get_window()->get_height();
	x = (x - imgX) / 2;
	y = (y - imgY) / 2;
	if (showText)
		image->render_to_drawable(videoBoard->get_window(),
				videoBoard->get_style()->get_black_gc(), 0, 0, x, y, imgX, imgY,
				Gdk::RGB_DITHER_NONE, 0, 0);
	return false;
}

int VideoBoard::getXID() {
	return GDK_WINDOW_XID(Glib::unwrap(videoBoard->get_window()));
}

bool VideoBoard::on_expose_event(GdkEventExpose* ev) {
	int x = videoBoard->get_window()->get_width();
	int y = videoBoard->get_window()->get_height();
	if (boardSizeX != x || boardSizeY != y) {
		videoBoard->get_window()->clear();
		x = (x - imgX) / 2;
		y = (y - imgY) / 2;
		if (showText)
			image->render_to_drawable(videoBoard->get_window(),
					videoBoard->get_style()->get_black_gc(), 0, 0, x, y, imgX,
					imgY, Gdk::RGB_DITHER_NONE, 0, 0);
		Glib::signal_timeout().connect(
				sigc::mem_fun(*this, &VideoBoard::on_timeout), 100);
	}
	return true;
}
