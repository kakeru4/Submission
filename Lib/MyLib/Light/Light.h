/*
* @file		Light.h
* @brief	Lightクラスヘッダ
* @author	matsuda
*/
#ifndef LIGHT_H
#define LIGHT_H

#include <d3dx9.h>

class Light
{
public:
	Light(LPDIRECT3DDEVICE9 pD3Device, D3DXVECTOR3 direction);
	Light(LPDIRECT3DDEVICE9 pD3Device, D3DXVECTOR3 lightPos, D3DXVECTOR3 direction);
	~Light();
	void LightSet();
	void LightUp();
private:
	LPDIRECT3DDEVICE9		m_pD3Device;		// Direct3Dのデバイス
	D3DLIGHT9				m_Light;			// ライト構造体
	D3DXVECTOR3				m_LightPos;			// ライトの位置
	D3DXVECTOR3             m_Direction;		// ライトの向き
	DWORD					m_AmbientColor;		// アンビエント色
};

#endif //LIGHT_H