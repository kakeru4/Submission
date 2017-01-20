/*
* @file		Collision.h
* @brief	Collisionクラスヘッダ
* @author	matsuda
*/#ifndef COLLISION_H
#define COLLISION_H

#include<d3dx9.h>

class Collision
{
public:
	enum COLLISION_ID
	{
		Chips,
		Fighter,
	};

	Collision(float radius, COLLISION_ID id);
	~Collision();
	void CreatSphere(IDirect3DDevice9* Device,float radius);
	void CreatBox();
	void SetData(const D3DXVECTOR3* pos);
	D3DXVECTOR3 GetPos();
	float GetRadius();
	void CheckState();
	bool InformCollision();
	bool GetIsHit();
private:
	D3DXVECTOR3 m_Pos;
	float		m_Radius;
	bool        m_IsHit;
	LPD3DXMESH m_pMesh;
	COLLISION_ID m_ID;
};
#endif //COLLISION_H
