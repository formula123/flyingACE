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


class EnemyLayer : public cocos2d::Layer{
public:
	EnemyLayer();
	~EnemyLayer();
	CREATE_FUNC(EnemyLayer);
	virtual bool init() override;
	void addEnemySprite(float useless);
	void enemyMoveFinished(Node* pSender);
	void startAddEnemy();
	void update(float useless) override;

	const cocos2d::Size winSize;
	cocos2d::Array* pAllEnemy;

	std::vector<std::string> enemyTextureName;
	std::vector<int> enemyFlyTime;

	const float  baseEnemyAppearProbability;
	const float deltaEnemyAppearProbability;
	float nowEnemyAppearProbability;


};

#endif /* ENEMYLAYER_H_ */
