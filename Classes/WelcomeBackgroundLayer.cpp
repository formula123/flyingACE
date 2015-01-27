/*
 * WelcomeBackgroundLayer.cpp
 *
 *  Created on: 2015年1月27日
 *      Author: netbeen
 */

#include "WelcomeBackgroundLayer.h"

USING_NS_CC;

bool WelcomeBackgroundLayer::init(){
	auto background = Sprite::createWithSpriteFrameName("img_bg_welcome.jpg");
	background->setAnchorPoint(Point(0,0));
	this->addChild(background);

	return true;
}
