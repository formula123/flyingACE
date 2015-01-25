/*
 * GameScene.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: netbeen
 */

#include "GameScene.h"

USING_NS_CC;

static Scene* _sharedGameScene = nullptr;

Scene* GameScene::getInstance() {
	if (!_sharedGameScene) {
		_sharedGameScene = Scene::create();

		GameBackgroundLayer* backgroundLayer = GameBackgroundLayer::getInstance();
		_sharedGameScene->addChild(backgroundLayer);
		UFOLayer* ufoLayer = UFOLayer::getInstance();
		_sharedGameScene->addChild(ufoLayer);
		BulletLayer* bulletLayer = BulletLayer::getInstance();
		_sharedGameScene->addChild(bulletLayer);
		EnemyLayer* enemyLayer = EnemyLayer::getInstance();
		_sharedGameScene->addChild(enemyLayer);
		PlaneLayer* planeLayer = PlaneLayer::getInstance();
		_sharedGameScene->addChild(planeLayer);
		ControlLayer* controlLayer = ControlLayer::getInstance();
		_sharedGameScene->addChild(controlLayer);
	}
	return _sharedGameScene;

}

