/*
 * EnemyLayer.h
 *
 *  Created on: 2015年1月17日
 *      Author: netbeen
 */

#ifndef ENEMYLAYER_H_
#define ENEMYLAYER_H_

#include <string>
#include <vector>
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "EnemyUserData.h"
#include "BulletLayer.h"
#include "BulletUserData.h"


class EnemyLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(EnemyLayer);
private:
	const float  baseEnemyAppearProbability;
	const float deltaEnemyAppearProbability;
	float nowEnemyAppearProbability;
	std::vector<std::string> enemyTextureName;
	std::vector<int> enemyFlyTime;
	std::vector<int> enemyInitHP;
	cocos2d::Vector<cocos2d::Sprite*> allEnemy;
	const cocos2d::Size winSize;

	EnemyLayer();
	~EnemyLayer();
	virtual bool init() override;
	void addEnemySprite(float useless);
	void enemyMoveFinished(Node* pSender);
	void startAddEnemy();
	void update(float useless) override;

};

#endif /* ENEMYLAYER_H_ */
