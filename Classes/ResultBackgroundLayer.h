/*
 * ResultBackgroundLayer.h
 *
 *  Created on: 2015年1月27日
 *      Author: netbeen
 */

#ifndef RESULTBACKGROUNDLAYER_H_
#define RESULTBACKGROUNDLAYER_H_

#include "cocos2d.h"

class ResultBackgroundLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(ResultBackgroundLayer);
private:
	virtual bool init() override;
};

#endif /* RESULTBACKGROUNDLAYER_H_ */
