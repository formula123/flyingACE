/*
 * BulletUserData.cpp
 *
 *  Created on: 2015年1月18日
 *      Author: netbeen
 */

#include "BulletUserData.h"

BulletUserData::BulletUserData(int initDamage, int initBulletLevel):damage(initDamage),bulletLevel(initBulletLevel){
}

int BulletUserData::getDamage(){
	return this->damage;
}

int BulletUserData::getBulletLevel(){
	return this->bulletLevel;
}
