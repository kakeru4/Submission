#include"Fighter.h"
#include "../CollisionManager/CollisionManager.h"
#include "../Collision/Collision.h"
Fighter::Fighter(D3DXVECTOR3* pos)
	:Object(pos)
{
	m_pCollision = new Collision(3.f, Collision::Fighter);
	Lib::GetInstance().LoadXFile(3,"../Resouce//ThunderFighter.x");
}

Fighter::~Fighter()
{
	delete m_pCollision;
}

void Fighter::Control()
{
	if (m_pCollision->InformCollision())
	{

	}
	m_pCollision->SetData(&m_ObjectPos);
}

void Fighter::Draw()
{
	TransWorld(m_ObjectPos);
	Lib::GetInstance().DrawXFile(3);
}