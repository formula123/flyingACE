/*
 * EnemyUserData.h
 *
 *  Created on: 2015年1月18日
 *      Author: netbeen
 */

#ifndef ENEMYUSERDATA_H_
#define ENEMYUSERDATA_H_

class EnemyUserData {
public:
	EnemyUserData(int initHP);
	void setIsDeleting();
	bool getIsDeleting();
	bool isAliveUnderAttack(int damage);
private:
	int HP;
	bool isDeleting;
};

#endif /* ENEMYUSERDATA_H_ */
