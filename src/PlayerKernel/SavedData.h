/*
 * SavedData.h
 *
 *  Created on: 16.8.2011
 *      Author: xgeier
 */

#ifndef SAVEDDATA_H_
#define SAVEDDATA_H_

class SavedData {
public:
	SavedData();
	virtual ~SavedData();
	void setResolution(int x, int y);
	void setPosition(double position);
	int getX();
	int getY();
	double getPosition();
private:
	int resX;
	int resY;
	int position;
};

#endif /* SAVEDDATA_H_ */
