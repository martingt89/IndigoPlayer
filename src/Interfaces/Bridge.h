/*
 * Bridge.h
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_

class Bridge {
public:
	Bridge();
	virtual ~Bridge();
	virtual void clickOpenButton() = 0;
	virtual void clickThisOptionsButton() = 0;
	virtual void setResolution(int width, int height) = 0;
	virtual void changeFullscreen() = 0;
	virtual void setFullscreen(bool full) = 0;
	virtual void setMaximalize(bool max) = 0;
	virtual void keyPressed(int control, int keyVal, unsigned short hardwareKey) = 0;
};

#endif /* BRIDGE_H_ */
