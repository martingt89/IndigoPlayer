/*
 * ClassHelper.cpp
 *
 *  Created on: 4.9.2011
 *      Author: xgeier
 */

#include "ClassHelper.h"

std::string ClassHelper::trimText(std::string text){
	text.erase(text.begin(), std::find_if(text.begin(), text.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	text.erase(std::find_if(text.rbegin(), text.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), text.end());
	return text;
}
