/*
* @file		Collision.cpp
* @brief	Collisionクラス実装
* @author	matsuda
*/

#include "Collision.h"
#include "../Lib/Lib.h"
#include "../CollisionManager/CollisionManager.h"

Collision::Collision(float radius, COLLISION_ID id)
	:m_Radius(radius)
	, m_IsHit(false)
	, m_pMesh(nullptr)
	, m_ID(id)
{
}


Collision::~Collision()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
	}
}

void Collision::SetData(const D3DXVECTOR3* pos)
{
	m_IsHit;
	m_Pos = *pos;
	CollisionManager::GetInstance().SetCollision(this);
}

void Collision::CreatSphere(IDirect3DDevice9* pDevice,float radius)
{
	D3DXCreateSphere(pDevice,radius,64,32,&m_pMesh,nullptr);
	m_pMesh->DrawSubset(0);
}

void Collision::CheckState()
{
	m_IsHit = true;
}

bool Collision::InformCollision()
{
	if (m_IsHit)
	{
		m_IsHit = false;
		return true;
	}
	return false;
}

D3DXVECTOR3 Collision::GetPos()
{
	return m_Pos;
}

float Collision::GetRadius()
{
	return m_Radius;
}

bool Collision::GetIsHit()
{
	return m_IsHit;
}