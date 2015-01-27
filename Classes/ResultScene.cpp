/*
 * ResultScene.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: netbeen
 */

#include "ResultScene.h"

USING_NS_CC;

Scene* ResultScene::resultScene = nullptr;

Scene* ResultScene::create() {
	resultScene = Scene::create();

	ResultBackgroundLayer* resultBackgroundLayer = ResultBackgroundLayer::create();
	resultBackgroundLayer->setParent(resultScene);
	resultScene->addChild(resultBackgroundLayer);

	ResultButtonLayer* resultButtonLayer = ResultButtonLayer::create();
	resultButtonLayer->setParent(resultScene);
	resultScene->addChild(resultButtonLayer);

	return resultScene;

}
