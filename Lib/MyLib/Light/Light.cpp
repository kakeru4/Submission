/*
* @file		Light.cpp
* @brief	Lightクラス実装
* @author	matsuda
*/

#include "Light.h"


Light::Light(LPDIRECT3DDEVICE9 pD3Device, D3DXVECTOR3 direction)
	: m_pD3Device(pD3Device)
	, m_Direction(direction)
	, m_AmbientColor(0x00111111)
{
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse.r = 1.0f;
	m_Light.Diffuse.g = 1.0f;
	m_Light.Diffuse.b = 1.0f;
	m_Light.Specular.r = 1.0f;
	m_Light.Specular.g = 1.0f;
	m_Light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &m_Direction);
	m_Light.Range = 500.0f;
}

Light::Light(LPDIRECT3DDEVICE9 pD3Device, D3DXVECTOR3 lightPos, D3DXVECTOR3 direction)
	: m_pD3Device(pD3Device)
	, m_Direction(direction)
	, m_LightPos(lightPos)
	, m_AmbientColor(0x00111111)
{
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = D3DLIGHT_SPOT;
	m_Light.Diffuse.r = 1.0f;
	m_Light.Diffuse.g = 1.0f;
	m_Light.Diffuse.b = 1.0f;
	m_Light.Specular.r = 1.0f;
	m_Light.Specular.g = 1.0f;
	m_Light.Specular.b = 1.0f;
	m_Light.Position = m_LightPos;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &m_Direction);
	m_Light.Range = 500.0f;
}


Light::~Light()
{

}

void Light::LightSet()
{
	m_pD3Device->SetLight(0, &m_Light);
	m_pD3Device->LightEnable(0, TRUE);
	m_pD3Device->SetRenderState(D3DRS_LIGHTING, TRUE);				     // ライトを有効にする
	m_pD3Device->SetRenderState(D3DRS_AMBIENT, m_AmbientColor);			 // アンビエントライト(環境光)を設定する
	m_pD3Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);		     // スペキュラ(鏡面反射)を有効にする
}