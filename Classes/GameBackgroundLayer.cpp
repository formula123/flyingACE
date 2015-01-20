/*
 * GameBackgroundLayer.cpp
 *
 *  Created on: 2015年1月15日
 *      Author: netbeen
 */

#include "GameBackgroundLayer.h"

USING_NS_CC;

const float backgroundMoveSpeed = 1;

static GameBackgroundLayer* _sharedGameBackgroundLayer = nullptr;

GameBackgroundLayer* GameBackgroundLayer::getInstance() {
	if (!_sharedGameBackgroundLayer) {
		_sharedGameBackgroundLayer = new (std::nothrow) GameBackgroundLayer();
		_sharedGameBackgroundLayer->init();
	}
	return _sharedGameBackgroundLayer;
}

bool GameBackgroundLayer::init(){
	background1 = Sprite::createWithSpriteFrameName("img_bg_1.jpg");
	background1->setAnchorPoint(Point(0,0));
	this->addChild(background1);

	background2 = Sprite::createWithSpriteFrameName("img_bg_1.jpg");
	background2->setAnchorPoint(Point(0,0));
	this->addChild(background2);

	scheduleUpdate();
	return true;
}

void GameBackgroundLayer::update(float useless){
	background1->setPositionY(background1->getPositionY() - backgroundMoveSpeed);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 1);
	if(background2->getPositionY() < 0){
		background1->setPositionY(0);
	}
}
