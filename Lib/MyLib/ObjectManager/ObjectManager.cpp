#include "ObjectManager.h"
#include "../Chips/Chips.h"
#include "../Sea/Sea.h"
#include "../Fighter/Fighter.h"
#include "../CollisionManager/CollisionManager.h"
ObjectManager::ObjectManager()
	:m_pChips(nullptr)
	, m_pSea(nullptr)
	, m_pFighter(nullptr)
{
	m_pChips = new Chips(&D3DXVECTOR3(0, 0, 0));
	m_pSea = new Sea(&D3DXVECTOR3(0, -2, 0));
	m_pFighter = new Fighter(&D3DXVECTOR3(0, 0, 5));

}


ObjectManager::~ObjectManager()
{
	delete m_pChips;
	delete m_pSea;
	delete m_pFighter;
}

void ObjectManager::Control()
{
	m_pChips->Control();
	m_pFighter->Control();
}

void ObjectManager::Draw()
{
	m_pChips->Draw();
	m_pSea->Draw();
	m_pFighter->Draw();
}

D3DXVECTOR3 ObjectManager::GetCameraPos()
{
	return m_pChips->GetCameraPos();
}

D3DXVECTOR3 ObjectManager::GetLookatPos()
{
	return m_pChips->GetLookatPos();
}

float ObjectManager::GetCameraAngle()
{
	return m_pChips->GetCameraAngle();
}

void ObjectManager::CameraTransform()
{
	m_pChips->CameraTransWorld(100.f);
}

D3DXVECTOR3 ObjectManager::GetChipsPos()
{
	return m_pChips->GetChipsPos();
}