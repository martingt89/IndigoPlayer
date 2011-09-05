/*
 * EnumTypes.h
 *
 *  Created on: 31.8.2011
 *      Author: xgeier
 */

#ifndef ENUMTYPES_H_
#define ENUMTYPES_H_

namespace IndigoPlayerEnum {
	enum ControlKey {
		NONE,
		CTRL,
		SHIFT,
		ALT,
		CAPSLOCK
	};

	enum Command {
		FULLUNFULLSCR,
		UNFULLSCR,
		FULLSCR,
		HALFSIZE,
		ORIGINALSIZE,
		MAXIMALIZESIZE,
		PLAYSTOPBUT,
		MUTEUNMUTE,
		SHORFORWARD,
		SHORBACKWARD,
		LONGFORWARD,
		LONGBACKWARD
	};
	enum OpenWindowNotebook{
		FILE,
		FOLDER,
		ANDVENCEDFILE,
		NETWORK,
		DVD
	};
}

#endif /* ENUMTYPES_H_ */
