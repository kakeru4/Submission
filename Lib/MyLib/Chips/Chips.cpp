#include "Chips.h"
#include "../Lib/Lib.h"
#include "../CameraController/CameraController.h"
#include "../CollisionManager/CollisionManager.h"
#include "../Collision/Collision.h"

Chips::Chips(D3DXVECTOR3* pos)
	:Object(pos)
	, m_CameraPos({ pos->x, pos->y, pos->z-50 })
	, m_LookatPos({ pos->x, pos->y, pos->z })
	, m_CameraAngle(45.f)
{
	m_pCollision = new Collision(3.f, Collision::Chips);
	Lib::GetInstance().LoadXFile(1,"../Resouce//Chips.x");
}


Chips::~Chips()
{
	delete m_pCollision;
}

void Chips::Control()
{
	
	if (Lib::GetInstance().CheckKey(DIK_RIGHT, RIGHT) == ON)
	{
		m_ObjectPos.x += 1;
	}

	if (Lib::GetInstance().CheckKey(DIK_LEFT, LEFT) == ON)
	{
		m_ObjectPos.x -= 1;
	}

	if (Lib::GetInstance().CheckKey(DIK_UP, UP) == ON)
	{
		m_ObjectPos.z += 1;
	}

	if (Lib::GetInstance().CheckKey(DIK_DOWN, DOWN) == ON)
	{
		m_ObjectPos.z -= 1;
	}

	if (Lib::GetInstance().CheckKey(DIK_A, A) == ON)
	{
		m_CameraPos.x -= 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_D, D) == ON)
	{
		m_CameraPos.x += 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_W, W) == ON)
	{
		m_CameraPos.y -= 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_S, S) == ON)
	{
		m_CameraPos.y += 10;
	}
	
	if (Lib::GetInstance().CheckKey(DIK_Q, Q) == ON)
	{
		m_CameraPos.z -= 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_E, E) == ON)
	{
		m_CameraPos.z += 10;
	}
	if (m_pCollision->InformCollision())
	{
	}
	m_pCollision->SetData(&m_ObjectPos);
}

void Chips::Draw()
{
	TransWorld(m_ObjectPos);
	if (Lib::GetInstance().CheckKey(DIK_P, P) == ON)
	{
		CameraController::GetInstance().TransformView(m_CameraPos, m_LookatPos, m_CameraAngle);
	}
	
	Lib::GetInstance().DrawXFile(1);
	m_pCollision->CreatSphere(Lib::GetInstance().GetDevice(),3.f);
	if (m_pCollision->GetIsHit())
	{
		Lib::GetInstance().DrawDebugFont("当たってます", 1400, 10);
	}
	else if (!m_pCollision->GetIsHit())
	{
		Lib::GetInstance().DrawDebugFont("当たってません", 1400, 10);
	}
}

void Chips::CameraTransWorld(float radius)
{
	D3DXVECTOR3		cameraPos(0.f, 0.f, -radius);
	D3DXVec3TransformCoord(&cameraPos, &cameraPos, &m_CameraRotation);
	D3DXVec3Add(&cameraPos, &cameraPos, &m_CameraPos);
	m_CameraPos.x = cameraPos.x;
	m_CameraPos.z = cameraPos.z;

	D3DXVECTOR3		lookatPos(0.f, 0.f, radius);
	D3DXVec3TransformCoord(&lookatPos, &lookatPos, &m_CameraRotation);
	D3DXVec3Add(&lookatPos, &lookatPos, &m_LookatPos);
	m_LookatPos.x = lookatPos.x;
	m_LookatPos.z = lookatPos.z;
}

D3DXVECTOR3 Chips::GetCameraPos()
{
	return m_CameraPos;
}

D3DXVECTOR3 Chips::GetLookatPos()
{
	return m_LookatPos;
}

float Chips::GetCameraAngle()
{
	return m_CameraAngle;
}

D3DXVECTOR3 Chips::GetChipsPos()
{
	return m_ObjectPos;
}