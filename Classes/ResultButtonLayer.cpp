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
	restartGameButton->setPosition(Director::getInstance()->getWinSize().width/2,400);
	this->addChild(restartGameButton);

	MenuItemSprite* startGameButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("startGameButton.png"), Sprite::createWithSpriteFrameName("startGameButton.png"), CC_CALLBACK_1(ResultButtonLayer::startGameButtonCallback, this));
	Menu* startGameButton = Menu::create(startGameButtonItemSprite, nullptr);
	startGameButton->setPosition(Director::getInstance()->getWinSize().width/2,330);
	this->addChild(startGameButton);

	return true;
}

void ResultButtonLayer::restartGameButtonCallback(Ref* pSender){
	Scene* welcomeScene = TransitionFade::create(2.0f,GameScene::create());
	Director::getInstance()->replaceScene(welcomeScene);
}

void ResultButtonLayer::startGameButtonCallback(Ref* pSender){
	Scene* welcomeScene = TransitionFade::create(2.0f,WelcomeScene::create());
	Director::getInstance()->replaceScene(welcomeScene);
}
