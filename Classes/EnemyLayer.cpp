/*
 * EnemyLayer.cpp
 *
 *  Created on: 2015年1月17日
 *      Author: netbeen
 */

#include "EnemyLayer.h"

USING_NS_CC;

EnemyLayer::EnemyLayer() :
		winSize(Director::getInstance()->getWinSize()), baseEnemyAppearProbability(0.1), deltaEnemyAppearProbability(0.005), nowEnemyAppearProbability(baseEnemyAppearProbability){
}

EnemyLayer::~EnemyLayer() {
}

bool EnemyLayer::init() {
	std::string name1 = "enemy1.png";
	std::string name2 = "enemy2.png";
	std::string name3 = "enemy3.png";
	enemyTextureName.push_back(name1);
	enemyTextureName.push_back(name2);
	enemyTextureName.push_back(name3);
	enemyFlyTime.push_back(10);
	enemyFlyTime.push_back(10);
	enemyFlyTime.push_back(5);
	enemyInitHP.push_back(100);
	enemyInitHP.push_back(200);
	enemyInitHP.push_back(150);
	startAddEnemy();
	this->scheduleUpdate();

	return true;
}

void EnemyLayer::addEnemySprite(float useless) {
	float testProbability = CCRANDOM_0_1();
	if(testProbability < nowEnemyAppearProbability) {
		int randomLevel = CCRANDOM_0_1() * 3;
		Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[randomLevel].c_str());
		int randomX = CCRANDOM_0_1()*winSize.width;
		enemySprite->setPosition(randomX, winSize.height +enemySprite->getContentSize().height/2 );
		enemySprite->setUserData(new EnemyUserData(enemyInitHP[randomLevel]));
		this->addChild(enemySprite);
		allEnemy.pushBack(enemySprite);

		FiniteTimeAction* enemyMove = MoveTo::create(enemyFlyTime[randomLevel], Point(randomX, - enemySprite->getContentSize().height/2));
		FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
		enemySprite->runAction(enemyAction);
	}
	nowEnemyAppearProbability += deltaEnemyAppearProbability;
}

void EnemyLayer::enemyMoveFinished(Node* pSender) {
	Sprite* enemy = (Sprite*) pSender;
	allEnemy.eraseObject(enemy);
	delete static_cast<EnemyUserData*>(enemy->getUserData());
	this->removeChild(enemy, true);
}

void EnemyLayer::startAddEnemy() {
	this->schedule(schedule_selector(EnemyLayer::addEnemySprite), 0.2f);
}

void EnemyLayer::update(float useless) {
	Animation* animationExplosion = AnimationCache::getInstance()->getAnimation("explosion");
	animationExplosion->setRestoreOriginalFrame(false);
	animationExplosion->setDelayPerUnit(0.5f / 9.0f);
	auto actionExplosion = Animate::create(animationExplosion);
	for( Sprite* enemy : this->allEnemy ){
		if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false) {
			for( Sprite* bullet : BulletLayer::getInstance()->allBullet ){
				if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())) {
					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
						enemy->stopAllActions();
						FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished,this));
						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
					}
					BulletLayer::getInstance()->bulletMoveFinished(bullet);
				}
			}
		}
		if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false && enemy->getBoundingBox().intersectsRect(PlaneLayer::getInstance()->myPlane->getBoundingBox())) {
			if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(9999) == false) {
				enemy->stopAllActions();
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
				static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
			}
		}
	}
}
