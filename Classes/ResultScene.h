/*
 * ResultScene.h
 *
 *  Created on: 2015年1月25日
 *      Author: netbeen
 */

#ifndef RESULTSCENE_H_
#define RESULTSCENE_H_

#include "cocos2d.h"
#include "ResultButtonLayer.h"

class ResultScene :public cocos2d::Scene{
public:
	static Scene* create();
private:
	static Scene* resultScene;
};

#endif /* RESULTSCENE_H_ */
