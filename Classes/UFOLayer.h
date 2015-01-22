/*
 * UFOLayer.h
 *
 *  Created on: 2015年1月21日
 *      Author: netbeen
 */

#ifndef UFOLAYER_H_
#define UFOLAYER_H_

#include <string>
#include <vector>
#include "cocos2d.h"
#include "ControlLayer.h"

class UFOLayer : public cocos2d::Layer{
public:
	static UFOLayer* getInstance();
	void addGiftSprite();
private:
	std::vector<std::string> giftTextureName;
	std::vector<int> giftFlyTime;
	cocos2d::Vector<cocos2d::Sprite*> allGift;
	cocos2d::Size winSize;

	virtual bool init() override;
	void giftMoveFinished(cocos2d::Node* pSender);
	UFOLayer();
	void update(float useless);
};

#endif /* UFOLAYER_H_ */
