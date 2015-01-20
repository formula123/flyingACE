/*
 * ControlLayer.h
 *
 *  Created on: 2015年1月20日
 *      Author: netbeen
 */

#ifndef CONTROLLAYER_H_
#define CONTROLLAYER_H_

#include <strstream>
#include "cocos2d.h"
#include "GameBackgroundLayer.h"

class ControlLayer : public cocos2d::Layer{
public:
	static ControlLayer* getInstance();
	void addScoreBy(int addScore);
private:
	int score;
	cocos2d::Label* scoreLabel;
	cocos2d::MenuItemSprite* pauseButtonItem;


	void updateScore();
	void menuPauseCallback(cocos2d::Ref* pSender);
	ControlLayer();
	virtual bool init() override;
};

#endif /* CONTROLLAYER_H_ */
