/*
 * EnemyUserData.cpp
 *
 *  Created on: 2015年1月18日
 *      Author: netbeen
 */

#include "EnemyUserData.h"

EnemyUserData::EnemyUserData(int initHP):isDeleting(false),HP(initHP){
}

void EnemyUserData::setIsDeleting(){
	this->isDeleting = true;
}

bool EnemyUserData::getIsDeleting(){
	return this->isDeleting;
}

bool EnemyUserData::isAliveUnderAttack(int damage){
	this->HP -= damage;
	if(this->HP <= 0){
		return false;
	}else{
		return true;
	}
}
