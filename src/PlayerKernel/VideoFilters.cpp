/*
 * VideoFilters.cpp
 *
 *  Created on: 16.8.2011
 *      Author: xgeier
 */

#include "VideoFilters.h"

VideoFilters::VideoFilters() {
	resizeUp = 0;
	resizeDown = 0;
	resizeLeft = 0;
	resizeRight = 0;
	rotateDeg = 0;
}

VideoFilters::~VideoFilters() {
}

void VideoFilters::resize(int up, int down, int left, int right) {
	resizeUp = up;
	resizeDown = down;
	resizeLeft = left;
	resizeRight = right;
}

void VideoFilters::rotate(int deg) {
	rotateDeg = deg;
}
void VideoFilters::getResize(int &up, int &down, int &left, int &right) {
	up = resizeUp;
	down = resizeDown;
	left = resizeLeft;
	right = resizeRight;
}
int VideoFilters::getRotate(){
	return rotateDeg;
}
