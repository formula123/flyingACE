/*
 * BulletLayer.h
 *
 *  Created on: 2015年1月16日
 *      Author: netbeen
 */

#ifndef BULLETLAYER_H_
#define BULLETLAYER_H_

#include "cocos2d.h"
#include "PlaneLayer.h"

class BulletLayer : public cocos2d::Layer{
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	virtual bool init() override;
	void addBullet(float useless);
	void bulletMoveFinished(Node* pSender);
	void startShooting();
	void stopShooting();

	cocos2d::Array* pAllBullet;
};

#endif /* BULLETLAYER_H_ */
