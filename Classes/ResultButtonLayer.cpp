/*
 * ResultButtonLayer.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: netbeen
 */

#include "ResultButtonLayer.h"

USING_NS_CC;

bool ResultButtonLayer::init() {
	MenuItemSprite* restartGameButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("restartGameButton.png"), Sprite::createWithSpriteFrameName("restartGameButton.png"), CC_CALLBACK_1(ResultButtonLayer::restartGameButtonCallback, this));
	Menu* restartGameButton = Menu::create(restartGameButtonItemSprite, nullptr);
	restartGameButton->setAnchorPoint(Point(0.0f, 1.0f));
	restartGameButton->setPosition(400,400);
	this->addChild(restartGameButton);

	return true;
}

void ResultButtonLayer::restartGameButtonCallback(Ref* pSender){
	Scene* welcomeScene = TransitionFade::create(2.0f,GameScene::create());
	Director::getInstance()->replaceScene(welcomeScene);
}
