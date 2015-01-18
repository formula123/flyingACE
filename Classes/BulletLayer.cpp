/*
 * BulletLayer.cpp
 *
 *  Created on: 2015年1月16日
 *      Author: netbeen
 */

#include "BulletLayer.h"

USING_NS_CC;

bool BulletLayer::init() {
	this->startShooting();
	return true;
}

void BulletLayer::addBullet(float useless) {
	Sprite* bullet = Sprite::createWithSpriteFrameName("bullet.png");

	Point planePosition = PlaneLayer::getInstance()->getChildByName("PLANE")->getPosition();
	Point bulletPosition = Point(planePosition.x, planePosition.y + PlaneLayer::getInstance()->getChildByName("PLANE")->getContentSize().height);
	bullet->setPosition(bulletPosition);
	pAllBullet->addObject(bullet);
	this->addChild(bullet);

	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition.y + (bullet->getContentSize().height / 2);
	float bulletFlySpeed = 320 / 1;		//320pixel/sec
	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

	FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove = CallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));

	auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
	bullet->runAction(bulleAction);
}

void BulletLayer::bulletMoveFinished(Node* pSender) {
	Sprite* bullet = (Sprite*) pSender;
	pAllBullet->removeObject(bullet);
	this->removeChild(bullet, true);
}

void BulletLayer::startShooting() {
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f);
}

void BulletLayer::stopShooting() {
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

BulletLayer::BulletLayer() {
	pAllBullet = Array::create();
	pAllBullet->retain();
}

BulletLayer::~BulletLayer() {
	pAllBullet->release();
	pAllBullet = nullptr;
}
