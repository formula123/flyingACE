/*
 * GameBackgroundLayer.h
 *
 *  Created on: 2015年1月15日
 *      Author: netbeen
 */

#ifndef GAMEBACKGROUNDLAYER_H_
#define GAMEBACKGROUNDLAYER_H_

#include "cocos2d.h"

class GameBackgroundLayer : public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameBackgroundLayer);
	void update(float useless) override;
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
};

#endif /* GAMEBACKGROUNDLAYER_H_ */
