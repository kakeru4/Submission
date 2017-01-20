#include "Object.h"
#include "../CameraController/CameraController.h"

Object::Object(D3DXVECTOR3* pos)
:m_pD3Device(Lib::GetInstance().GetDevice())
,m_ObjectPos(*pos)
{
}


Object::~Object()
{
}

void Object::Draw()
{

}

void Object::Control()
{

}

void Object::TransWorld(D3DXVECTOR3 pos)
{
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);
}