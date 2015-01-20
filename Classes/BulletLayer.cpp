/*
 * BulletLayer.cpp
 *
 *  Created on: 2015年1月16日
 *      Author: netbeen
 */

#include "BulletLayer.h"

USING_NS_CC;

static BulletLayer* _sharedBulletLayer = nullptr;

BulletLayer* BulletLayer::getInstance() {
	if (!_sharedBulletLayer) {
		_sharedBulletLayer = new (std::nothrow) BulletLayer();
		_sharedBulletLayer->init();
	}
	return _sharedBulletLayer;
}

bool BulletLayer::init() {
	bulletBatchNode = SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet3.png")->getTexture());
	this->addChild(bulletBatchNode);
	this->startShooting();
	return true;
}

void BulletLayer::addBullet(float useless) {
	Sprite* bullet = Sprite::createWithSpriteFrameName("bullet3.png");

	Point planePosition = PlaneLayer::getInstance()->getChildByName("PLANE")->getPosition();
	Point bulletPosition = Point(planePosition.x, planePosition.y + PlaneLayer::getInstance()->getChildByName("PLANE")->getContentSize().height);
	bullet->setPosition(bulletPosition);
	bullet->setUserData(new BulletUserData(eachBulletDamage));
	allBullet.pushBack(bullet);
	this->bulletBatchNode->addChild(bullet);

	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition.y + (bullet->getContentSize().height / 2);
	float bulletFlySpeed = 1000 / 1;
	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

	FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
	bullet->runAction(bulleAction);
}

void BulletLayer::bulletMoveFinished(Node* pSender) {
	Sprite* bullet = static_cast<Sprite*>(pSender);
	delete static_cast<BulletUserData*>(bullet->getUserData());
	allBullet.eraseObject(bullet);
	this->bulletBatchNode->removeChild(bullet, true);
}

void BulletLayer::startShooting() {
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f);
}

void BulletLayer::stopShooting() {
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

BulletLayer::BulletLayer():eachBulletDamage(100),bulletBatchNode(nullptr){
}

BulletLayer::~BulletLayer() {
}
