/*
 * PlaneLayer.cpp
 *
 *  Created on: 2015年1月16日
 *      Author: netbeen
 */

#include "PlaneLayer.h"

USING_NS_CC;

static PlaneLayer* _sharedPlaneLayer = nullptr;

PlaneLayer* PlaneLayer::getInstance() {
	if (!_sharedPlaneLayer) {
		_sharedPlaneLayer = new (std::nothrow) PlaneLayer();
		_sharedPlaneLayer->init();
	}
	return _sharedPlaneLayer;
}

bool PlaneLayer::init() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlaneLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlaneLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	myPlane = Sprite::createWithSpriteFrameName("myPlane.png");
	myPlane->setAnchorPoint(Point(0.5, 0));
	myPlane->setPosition(winSize.width / 2, 0);
	this->addChild(myPlane, 0, "PLANE");
	return true;
}

PlaneLayer::PlaneLayer() :
		myPlane(nullptr), winSize(Director::getInstance()->getWinSize()) {
}

bool PlaneLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	return true;
}

void PlaneLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	myPlane->setPosition(myPlane->getPosition() + touch->getDelta());
	if (myPlane->getPositionX()  < 0) {
		myPlane->setPositionX(0);
	} else if (myPlane->getPositionX()  > winSize.width) {
		myPlane->setPositionX(winSize.width);
	}
	if (myPlane->getPositionY() < 0) {
		myPlane->setPositionY(0);
	} else if (myPlane->getPositionY() + myPlane->getContentSize().height > winSize.height) {
		myPlane->setPositionY(winSize.height - myPlane->getContentSize().height);
	}
}

Sprite* PlaneLayer::getMyPlane(){
	return this->myPlane;
}
