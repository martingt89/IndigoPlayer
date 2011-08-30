/*
 * Callable.h
 *
 *  Created on: 29.8.2011
 *      Author: xgeier
 */

#ifndef CALLABLE_H_
#define CALLABLE_H_

namespace IndigoPlayerCommand{
	enum Command{
		FULLUNFULLSCR,
		UNFULLSCR,
		FULLSCR,
		HALFSIZE,
		ORIGINALSIZE,
		MAXIMALIZESIZE,
		PLAYSTOPBUT,
		MUTEUNMUTE
	};
}

class Callable {
public:
	Callable();
	virtual ~Callable();
	virtual void call(IndigoPlayerCommand::Command command) = 0;
};

#endif /* CALLABLE_H_ */
