/*
 * GameScene.h
 *
 *  Created on: 2015年1月25日
 *      Author: netbeen
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"
#include "UFOLayer.h"

class GameScene : public cocos2d::Scene{
public:
	static cocos2d::Scene* getInstance();
private:
};

#endif /* GAMESCENE_H_ */
