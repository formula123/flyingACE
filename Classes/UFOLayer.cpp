/*
 * UFOLayer.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: netbeen
 */

#include "UFOLayer.h"

USING_NS_CC;

static UFOLayer* _sharedUFOLayer = nullptr;

UFOLayer* UFOLayer::getInstance() {
	if (!_sharedUFOLayer) {
		_sharedUFOLayer = new (std::nothrow) UFOLayer();
		_sharedUFOLayer->init();
	}
	return _sharedUFOLayer;
}

UFOLayer::UFOLayer() :
		winSize(Director::getInstance()->getWinSize()) {

}

bool UFOLayer::init() {
	std::string name1 = "bigBombGet.png";
	std::string name2 = "bulletUpgrade.png";
	giftTextureName.push_back(name1);
	giftTextureName.push_back(name2);

	giftFlyTime.push_back(7);
	giftFlyTime.push_back(7);

	return true;
}

void UFOLayer::addGiftSprite() {
	float testProbability = CCRANDOM_0_1();
	int giftKinds;
	if(testProbability < 0.5) {
		giftKinds = 0;
	} else {
		giftKinds = 1;
	}
	Sprite* giftSprite = Sprite::createWithSpriteFrameName(giftTextureName[giftKinds].c_str());
	int randomX = CCRANDOM_0_1()*winSize.width;
	giftSprite->setPosition(randomX, winSize.height +giftSprite->getContentSize().height/2 );
	this->addChild(giftSprite);
	allGift.pushBack(giftSprite);

	FiniteTimeAction* giftMove = MoveTo::create(giftFlyTime[giftKinds], Point(randomX, - giftSprite->getContentSize().height/2));
	FiniteTimeAction* giftRemove = CallFuncN::create(CC_CALLBACK_1(UFOLayer::giftMoveFinished, this));
	Action* giftAction = Sequence::create(giftMove, giftRemove, NULL);
	giftSprite->runAction(giftAction);
}

void UFOLayer::giftMoveFinished(Node* pSender) {
	Sprite* gift = (Sprite*) pSender;
	allGift.eraseObject(gift);
	this->removeChild(gift, true);
}
