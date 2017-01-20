/*
* @file		Light.h
* @brief	Light�N���X�w�b�_
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
	LPDIRECT3DDEVICE9		m_pD3Device;		// Direct3D�̃f�o�C�X
	D3DLIGHT9				m_Light;			// ���C�g�\����
	D3DXVECTOR3				m_LightPos;			// ���C�g�̈ʒu
	D3DXVECTOR3             m_Direction;		// ���C�g�̌���
	DWORD					m_AmbientColor;		// �A���r�G���g�F
};

#endif //LIGHT_H