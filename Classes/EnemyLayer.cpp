/*
 * EnemyLayer.cpp
 *
 *  Created on: 2015年1月17日
 *      Author: netbeen
 */

#include "EnemyLayer.h"

USING_NS_CC;

static EnemyLayer* _sharedEnemyLayer = nullptr;

EnemyLayer* EnemyLayer::getInstance() {
	if (!_sharedEnemyLayer) {
		_sharedEnemyLayer = new (std::nothrow) EnemyLayer();
		_sharedEnemyLayer->init();
	}
	return _sharedEnemyLayer;
}

EnemyLayer::EnemyLayer() :
		winSize(Director::getInstance()->getWinSize()), baseEnemyAppearProbability(0.4), deltaEnemyAppearProbability(0.007), nowEnemyAppearProbability(baseEnemyAppearProbability),bossAppeared(false) {
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
	enemyInitHP.push_back(200);
	enemyInitHP.push_back(400);
	enemyInitHP.push_back(400);
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
	if(nowEnemyAppearProbability > 1) {
		this->stopAddEnemy();
		addBossSprite();
	}
}

void EnemyLayer::enemyMoveFinished(Node* pSender) {
	Sprite* enemy = (Sprite*) pSender;
	allEnemy.eraseObject(enemy);
	delete static_cast<EnemyUserData*>(enemy->getUserData());
	this->removeChild(enemy, true);
}

void EnemyLayer::startAddEnemy() {
	this->schedule(schedule_selector(EnemyLayer::addEnemySprite), 0.5f);
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
			for (Sprite* bullet : BulletLayer::getInstance()->allBullet) {
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				//判断子弹是否与敌机碰撞
				if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())) {
					//读取子弹的伤害，给敌机造成伤害
					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
						enemy->stopAllActions();
						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
						//摧毁敌机后加分
						ControlLayer::getInstance()->addScoreBy(100);
					}
					//end读取子弹的伤害，给敌机造成伤害

					//回收子弹
					BulletLayer::getInstance()->bulletMoveFinished(bullet);
				}
				//end判断子弹是否与敌机碰撞

				//判断我方飞机是否与敌机碰撞
				if (enemy->getBoundingBox().intersectsRect(PlaneLayer::getInstance()->getMyPlane()->getBoundingBox()) && static_cast<PlaneUserData*>(PlaneLayer::getInstance()->getMyPlane()->getUserData())->getHP() > 0) {
					//给敌机造成碰撞伤害
					if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(400) == false) {
						enemy->stopAllActions();
						static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
						enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));

						//撞毁敌机后加分
						ControlLayer::getInstance()->addScoreBy(100);
					}
					//end给敌机造成碰撞伤害

					//给我方飞机造成碰撞伤害
					if (static_cast<PlaneUserData*>(PlaneLayer::getInstance()->getMyPlane()->getUserData())->isAliveUnderAttack(200) == false) {
						BulletLayer::getInstance()->stopShooting();
						PlaneLayer::getInstance()->getMyPlane()->runAction(Sequence::create(actionExplosion, NULL));
						scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack),1.0f);
					}
					//end给我方飞机造成碰撞伤害

					//更新HP指示器
					ControlLayer::getInstance()->updateHPIndicator();
				}
				//end判断我方飞机是否与敌机碰撞
			}
		}
		//end判断敌机是否正在爆炸

	}
}

void EnemyLayer::addBossSprite() {
	Sprite* bossSprite = Sprite::createWithSpriteFrameName("enemyBoss.png");
	bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
	bossSprite->setUserData(new EnemyUserData(6000));
	this->addChild(bossSprite);
	allEnemy.pushBack(bossSprite);

	FiniteTimeAction* enemyMove = MoveTo::create(15, Point(winSize.width / 2, -bossSprite->getContentSize().height / 2));
	FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
	Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
	bossSprite->runAction(enemyAction);

	this->bossAppeared = true;
}

void EnemyLayer::changeSceneCallBack(float useless){
	Scene* resultSceneWithAnimation = TransitionFade::create(2.0f,ResultScene::getInstance());
	Director::getInstance()->replaceScene(resultSceneWithAnimation);
}
