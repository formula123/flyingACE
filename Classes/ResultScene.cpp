/*
 * ResultScene.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: netbeen
 */

#include "ResultScene.h"

USING_NS_CC;

static Scene* _sharedResultScene = nullptr;

Scene* ResultScene::getInstance() {
	if (!_sharedResultScene) {
		_sharedResultScene = Scene::create();
	}
	return _sharedResultScene;

}
