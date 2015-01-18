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
	EnemyUserData(bool inputIsDeleting);
	void setIsDeleting(bool inputIsDeleting);
	bool getIsDeleting();
private:
	bool isDeleting;
};

#endif /* ENEMYUSERDATA_H_ */
