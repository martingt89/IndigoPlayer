/*
 * VideoFilters.h
 *
 *  Created on: 2.9.2011
 *      Author: xgeier
 */

#ifndef VIDEOFILTERS_H_
#define VIDEOFILTERS_H_

class VideoFilters {
public:
	VideoFilters();
	virtual ~VideoFilters();
	virtual void setRotateFilter(int degrees, bool apply=false) = 0;
	virtual void cropFilter(int top, int right, int botton, int left, bool apply=false) = 0;
	virtual void setPlaySpeed(double speed) = 0;
	virtual void apply() = 0;
};

#endif /* VIDEOFILTERS_H_ */
