/*
 * PlaneLayer.h
 *
 *  Created on: 2015年1月16日
 *      Author: netbeen
 */

#ifndef PLANELAYER_H_
#define PLANELAYER_H_

#include "cocos2d.h"

class PlaneLayer : public cocos2d::Layer{
public:
	static PlaneLayer* getInstance();
	virtual bool init() override;
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    cocos2d::Sprite* myPlane;
private:
	PlaneLayer();
	const cocos2d::Size winSize;


};

#endif /* PLANELAYER_H_ */
