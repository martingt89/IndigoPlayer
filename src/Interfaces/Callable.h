/*
 * Callable.h
 *
 *  Created on: 29.8.2011
 *      Author: xgeier
 */

#ifndef CALLABLE_H_
#define CALLABLE_H_

#include "../../EnumTypes.h"
#include <list>

class Callable {
public:
	Callable();
	virtual ~Callable();
	virtual void call(IndigoPlayerEnum::Command command) = 0;
	virtual std::list<IndigoPlayerEnum::Command> getCommandList() = 0;
};

#endif /* CALLABLE_H_ */
