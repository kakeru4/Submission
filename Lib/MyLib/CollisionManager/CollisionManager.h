/*
* @file		CollisionManager.h
* @brief	CollisionManagerクラスヘッダ
* @author	matsuda
*/
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>

class Collision;

class CollisionManager
{
public:
	~CollisionManager();

	static CollisionManager&GetInstance()
	{
		static CollisionManager collisionmanager;
		return collisionmanager;
	}

	void SetCollision(Collision* collision);

	void CheckCollision();

	void ClearData();

private:
	std::vector<Collision*>		m_Collision;

	CollisionManager();
};
#endif //COLLISIONMANAGER_H
