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
	this->startShooting();
	return true;
}

void BulletLayer::addBullet(float useless) {
	Sprite* bullet = Sprite::createWithSpriteFrameName("bullet.png");

	Point planePosition = PlaneLayer::getInstance()->getChildByName("PLANE")->getPosition();
	Point bulletPosition = Point(planePosition.x, planePosition.y + PlaneLayer::getInstance()->getChildByName("PLANE")->getContentSize().height);
	bullet->setPosition(bulletPosition);
	bullet->setUserData(new BulletUserData(eachBulletDamage));
	pAllBullet->addObject(bullet);
	this->addChild(bullet);

	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition.y + (bullet->getContentSize().height / 2);
	float bulletFlySpeed = 320 / 1;
	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

	FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove = CallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));

	auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
	bullet->runAction(bulleAction);
}

void BulletLayer::bulletMoveFinished(Node* pSender) {
	Sprite* bullet = static_cast<Sprite*>(pSender);
	delete static_cast<BulletUserData*>(bullet->getUserData());
	pAllBullet->removeObject(bullet);
	this->removeChild(bullet, true);
}

void BulletLayer::startShooting() {
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f);
}

void BulletLayer::stopShooting() {
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

BulletLayer::BulletLayer():eachBulletDamage(100){
	pAllBullet = Array::create();
	pAllBullet->retain();
}

BulletLayer::~BulletLayer() {
	pAllBullet->release();
	pAllBullet = nullptr;
}
