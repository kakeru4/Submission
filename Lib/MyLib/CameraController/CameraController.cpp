/*
* @file		CameraContoller.cpp
* @brief	CameraContollerクラス実装
* @author	matsuda
*/
#include "CameraController.h"
#include "../Lib/Lib.h"
#include "../Camera/Camera.h"
#include "../ObjectManager/ObjectManager.h"

CameraController::CameraController()
	:m_pCamera(new Camera(Lib::GetInstance().GetDevice()))
	, m_CameraPos(D3DXVECTOR3(0.0f, 0.0f, -10.0f))
	, m_LookatPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_CameraAngle(45.f)
	, m_IsZoom(false)
	, m_NormalAngle(50.f)
	, m_ZoomAngle(10.f)
	, m_Rad(60.f)
	, m_Range(5.0f)
	, m_Moveabs(2.4f)
	, m_RotationSpeed(1.0f)
{
	// アスペクト比の設定
	float winWidth = static_cast<float>(Lib::GetInstance().GetWindowWidth());
	float winHeight = static_cast<float>(Lib::GetInstance().GetWindowHeight());
	m_pCamera->InitWindowSize(winWidth, winHeight);

	// 最遠点の設定
    m_farZ = 10000.f;
	m_pCamera->SetFarZ(m_farZ);
}


CameraController::~CameraController()
{
	delete m_pCamera;
}

void CameraController::Control()
{
	D3DXMATRIX		matRotation; // 回転行列

	if (Lib::GetInstance().CheckKey(DIK_A, A) == ON)
	{
		m_CameraPos.x -= 2;
	}

	if (Lib::GetInstance().CheckKey(DIK_D, D) == ON)
	{
		m_CameraPos.x += 2;
	}

	if (Lib::GetInstance().CheckKey(DIK_W, W) == ON)
	{
		m_CameraPos.y += 2;
	}

	if (Lib::GetInstance().CheckKey(DIK_S, S) == ON)
	{
		m_CameraPos.y -= 2;
	}

	if (Lib::GetInstance().CheckKey(DIK_Q, Q) == ON)
	{
		m_CameraPos.z -= 2;
	}

	if (Lib::GetInstance().CheckKey(DIK_E, E) == ON)
	{
		m_CameraPos.z += 2;
	}

	if (Lib::GetInstance().CheckKey(DIK_1,ONE) == ON)
	{
		m_CameraAngle = m_ZoomAngle;
		m_IsZoom = true;
	}
	else if (Lib::GetInstance().CheckKey(DIK_1, ONE) == OFF)
	{
		m_CameraAngle = m_NormalAngle;
		m_IsZoom = false;
	}
	/*if (Lib::GetInstance().CheckKey(DIK_2, TWO) == ON)
	{
		m_CameraAngle = m_ZoomAngle;
		m_IsZoom = true;
	}
	else if (Lib::GetInstance().CheckKey(DIK_2, TWO) == OFF)
	{
		m_CameraAngle = m_NormalAngle;
		m_IsZoom = false;
	}*/
	if (Lib::GetInstance().CheckKey(DIK_Q, Q) == ON)
	{
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(-m_RotationSpeed));

		D3DXVECTOR3 pos = m_CameraPos - m_LookatPos;

		D3DXVec3TransformCoord(&pos, &pos, &matRotation);

		m_CameraPos = pos + m_LookatPos;
	}
	if (Lib::GetInstance().CheckKey(DIK_S, S) == ON)
	{
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_RotationSpeed));

		D3DXVECTOR3 pos = m_CameraPos - m_LookatPos;

		D3DXVec3TransformCoord(&pos, &pos, &matRotation);

		m_CameraPos = pos + m_LookatPos;
	}

}

// 座標変換関数
void CameraController::TransformView()
{
	m_pCamera->LookInCamera(&m_CameraPos, &m_LookatPos, m_CameraAngle);
}

void CameraController::TransformView(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookPt, float angle)
{
	m_pCamera->LookInCamera(&vEyePt, &vLookPt, angle);
}

