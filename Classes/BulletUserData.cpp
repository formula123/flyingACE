/*
 * BulletUserData.cpp
 *
 *  Created on: 2015年1月18日
 *      Author: netbeen
 */

#include "BulletUserData.h"

BulletUserData::BulletUserData(int initDamage):damage(initDamage){
}

int BulletUserData::getDamage(){
	return this->damage;
}
