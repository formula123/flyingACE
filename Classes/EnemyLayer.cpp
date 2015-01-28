/*
 * EnemyLayer.cpp
 *
 *  Created on: 2015年1月17日
 *      Author: netbeen
 */

#include "EnemyLayer.h"

#include "PlaneLayer.h"
#include "EnemyUserData.h"
#include "BulletLayer.h"
#include "BulletUserData.h"
#include "PlaneLayer.h"
#include "PlaneUserData.h"
#include "ControlLayer.h"
#include "ResultScene.h"
#include "GameScene.h"

USING_NS_CC;


EnemyLayer::EnemyLayer() :
		winSize(Director::getInstance()->getWinSize()), baseEnemyAppearProbability(UserDefault::getInstance()->getFloatForKey("probabilityOfBaseEnemyAppear")), deltaEnemyAppearProbability(UserDefault::getInstance()->getFloatForKey("probabilityOfDeltaEnemyAppear")), nowEnemyAppearProbability(baseEnemyAppearProbability),bossAppeared(false) {
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

	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy1"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy2"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy3"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy1"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy2"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy3"));
	startAddEnemy();
	this->scheduleUpdate();

	bossWarning = Sprite::createWithSpriteFrameName("bossWarning.png");
	bossWarning->setPosition(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2);
	bossWarning->setScale(3.0f);
	bossWarning->setOpacity(0);
	this->addChild(bossWarning,128);

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
	if(nowEnemyAppearProbability > 1) {
		this->stopAddEnemy();
		this->setBossWarningOn();
		this->addBossSprite();
	}
}

void EnemyLayer::enemyMoveFinished(Node* pSender) {
	Sprite* enemy = (Sprite*) pSender;
	allEnemy.eraseObject(enemy);
	delete static_cast<EnemyUserData*>(enemy->getUserData());
	this->removeChild(enemy, true);
}

void EnemyLayer::startAddEnemy() {
	this->schedule(schedule_selector(EnemyLayer::addEnemySprite),UserDefault::getInstance()->getFloatForKey("intervalOfAddEnemy"));
}

void EnemyLayer::stopAddEnemy() {
	this->unschedule(schedule_selector(EnemyLayer::addEnemySprite));
}

void EnemyLayer::update(float useless) {
	Animation* animationExplosion = AnimationCache::getInstance()->getAnimation("explosion");
	animationExplosion->setRestoreOriginalFrame(false);
	animationExplosion->setDelayPerUnit(0.5f / 9.0f);
	auto actionExplosion = Animate::create(animationExplosion);

	//判断是否已经通关
	if((allEnemy.empty() == true) && (this->bossAppeared == true)){
		scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack),1.0f);
	}

	//遍历敌机
	for (Sprite* enemy : this->allEnemy) {
		//判断敌机是否正在爆炸
		if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false) {
			for (Sprite* bullet : static_cast<GameScene*>(this->getParent())->getBulletLayer()->allBullet) {
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				//判断子弹是否与敌机碰撞，之所以要重复判断是否isDeleting是为了防止两个弹头同时命中目标会造成程序崩溃的bug
				if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false)) {

					//读取子弹的伤害，给敌机造成伤害
					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
						enemy->stopAllActions();
						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
						//摧毁敌机后加分
						static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(100);
					}
					//end读取子弹的伤害，给敌机造成伤害

					//回收子弹
					static_cast<GameScene*>(this->getParent())->getBulletLayer()->bulletMoveFinished(bullet);
				}
				//end判断子弹是否与敌机碰撞

				//判断我方飞机是否与敌机碰撞
				if (enemy->getBoundingBox().intersectsRect(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getBoundingBox()) && static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->getHP() > 0) {
					//给敌机造成碰撞伤害
					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(400) == false) {
						enemy->stopAllActions();
						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));

						//撞毁敌机后加分
						static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(100);
					}
					//end给敌机造成碰撞伤害

					//给我方飞机造成碰撞伤害
					if (static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->isAliveUnderAttack(200) == false) {
						static_cast<GameScene*>(this->getParent())->getBulletLayer()->stopShooting();
						static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->runAction(Sequence::create(actionExplosion, NULL));
						scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack),1.0f);
					}
					//end给我方飞机造成碰撞伤害

					//更新HP指示器
					static_cast<GameScene*>(this->getParent())->getControlLayer()->updateHPIndicator();
				}
				//end判断我方飞机是否与敌机碰撞
			}
		}
		//end判断敌机是否正在爆炸
	}
	//end遍历敌机
}

void EnemyLayer::addBossSprite() {
	Sprite* bossSprite = Sprite::createWithSpriteFrameName("enemyBoss.png");
	bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
	bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss")));
	this->addChild(bossSprite);
	allEnemy.pushBack(bossSprite);

	FiniteTimeAction* enemyMove = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBoss"), Point(winSize.width / 2, -bossSprite->getContentSize().height / 2));
	FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
	Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
	bossSprite->runAction(enemyAction);

	this->bossAppeared = true;
}

void EnemyLayer::changeSceneCallBack(float useless){
	Scene* resultSceneWithAnimation = TransitionFade::create(2.0f,ResultScene::create());
	Director::getInstance()->replaceScene(resultSceneWithAnimation);
}

void EnemyLayer::setBossWarningOn(){
	Sequence* sequenceFront = Sequence::create(FadeIn::create(0.5f), FadeOut::create(1.5f),FadeIn::create(0.5f), FadeOut::create(2.0f), NULL);
	this->bossWarning->runAction(sequenceFront);
}
