/*
 * SelectBackground.cpp
 *
 *  Created on: 2015年1月30日
 *      Author: netbeen
 */

#include "SelectBackgroundLayer.h"

USING_NS_CC;

bool SelectBackgroundLayer::init() {
	Sprite* background = Sprite::createWithSpriteFrameName("selectSceneBackground.jpg");
	background->setScale(2.0f);
	background->setAnchorPoint(Point(0,0));
	this->addChild(background);
	return true;
}
