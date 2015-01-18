/*
 * EnemyUserData.cpp
 *
 *  Created on: 2015年1月18日
 *      Author: netbeen
 */

#include "EnemyUserData.h"

EnemyUserData::EnemyUserData(bool inputIsDeleting):isDeleting(inputIsDeleting){

}

void EnemyUserData::setIsDeleting(bool inputIsDeleting){
	this->isDeleting = inputIsDeleting;

}

bool EnemyUserData::getIsDeleting(){
	return this->isDeleting;
}

