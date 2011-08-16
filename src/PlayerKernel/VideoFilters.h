/*
 * VideoFilters.h
 *
 *  Created on: 16.8.2011
 *      Author: xgeier
 */

#ifndef VIDEOFILTERS_H_
#define VIDEOFILTERS_H_

class VideoFilters {
public:
	VideoFilters();
	virtual ~VideoFilters();
	void resize(int up, int down, int left, int right);
	void rotate(int deg);
	void getResize(int &up, int &down, int &left, int &right);
	int getRotate();
private:
	int resizeUp;
	int resizeDown;
	int resizeLeft;
	int resizeRight;
	int rotateDeg;
};

#endif /* VIDEOFILTERS_H_ */
