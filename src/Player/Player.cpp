/*
 * Player.cpp
 *
 *  Created on: 25.7.2011
 *      Author: xgeier
 */

#include "Player.h"

#include <iostream>

Player::Player(BasePlayerWindow *bsw) {
	basePlayerWindow = bsw;
	basePlayerWindow->setSignalListener(this);
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::clickPlay(){

}
void Player::clickStop(){

}
void Player::clickForward(){
	basePlayerWindow->setDuration(100);
}
void Player::clickBackward(){
	basePlayerWindow->setPosition(20);
}
void Player::clickCancel(){
	basePlayerWindow->clearTime();
}
void Player::clickFullscreen(){
	basePlayerWindow->openFullscreen();
}
void Player::clickThisOptions(){

}
void Player::clickPlaylist(){

}
void Player::clickKill(){

}
void Player::clickOpen(){

}
void Player::clickRewind(){

}
void Player::clickMute(){

}
void Player::clickSound(){

}
void Player::changeTimeLine(){

}
void Player::changeSoundLevel(){

}
