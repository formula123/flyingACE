/*
 * ControlLayer.cpp
 *
 *  Created on: 2015年1月20日
 *      Author: netbeen
 */

#include "ControlLayer.h"

#include <iostream>
USING_NS_CC;

static ControlLayer* _sharedControlLayer = nullptr;

ControlLayer::ControlLayer() :
		score(0), scoreLabel(nullptr),pauseButtonItem(nullptr) {
}

ControlLayer* ControlLayer::getInstance() {
	if (!_sharedControlLayer) {
		_sharedControlLayer = new (std::nothrow) ControlLayer();
		_sharedControlLayer->init();
	}
	return _sharedControlLayer;
}

void ControlLayer::addScoreBy(int addScore) {
	this->score += addScore;
	this->updateScore();
	return;
}

bool ControlLayer::init() {
	scoreLabel = Label::createWithTTF("0", "fonts/MarkerFelt.ttf", 60);
	scoreLabel->setAnchorPoint(Point(1.0f, 1.0f));
	scoreLabel->setPosition(Director::getInstance()->getWinSize().width - 50, Director::getInstance()->getWinSize().height - 50);
	this->addChild(scoreLabel);

	pauseButtonItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pauseButton.png"),Sprite::createWithSpriteFrameName("pauseButton.png"), CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));
	auto pauseButton = Menu::create(pauseButtonItem, nullptr);
	pauseButton->setAnchorPoint(Point(0.0f, 1.0f));
	pauseButton->setPosition(50, Director::getInstance()->getWinSize().height-50);
	this->addChild(pauseButton);

	return true;
}

void ControlLayer::updateScore(){
	std::string strScore;
	std::strstream ss;
	ss << this->score;
	ss >> strScore;
	scoreLabel->setString(strScore.c_str());
}

void ControlLayer::menuPauseCallback(Ref* pSender) {
	if(Director::getInstance()->isPaused()){
		Director::getInstance()->resume();
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
	}else{
		Director::getInstance()->pause();
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("startButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("startButton.png"));
	}
}
