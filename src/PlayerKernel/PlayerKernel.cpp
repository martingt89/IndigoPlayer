/*
 * PlayerKernel.cpp
 *
 *  Created on: 8.8.2011
 *      Author: xgeier
 */

#include "PlayerKernel.h"

PlayerKernel::PlayerKernel() {
	// TODO Auto-generated constructor stub

}

PlayerKernel::~PlayerKernel() {
	// TODO Auto-generated destructor stub
}

/*
 * 1. vygenerujem spustaci skript
 * 2. vytvor pipu, fork, exec
 * 3. vytvor thread, citaj pipu, ak nieco dojde posli vyssie cez dispatchera
 *
 */
