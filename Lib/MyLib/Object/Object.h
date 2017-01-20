#ifndef OBJECT_H
#define OBJECT_H

#include<d3dx9.h>
#include "../Lib/Lib.h"


class CameraController;
class Collision;

class Object
{
public:
	Object(D3DXVECTOR3* pos);
	virtual ~Object();
	virtual void Draw();
	virtual void Control();
	void TransWorld(D3DXVECTOR3 pos);
private:
protected:
	IDirect3DDevice9*		m_pD3Device;			// Direct3Dのデバイス
	D3DXVECTOR3		        m_ObjectPos;				// 座標
	CameraController*		m_pCameraControllerler;		// カメラコントローラー
	Collision*       m_pCollision;
};
#endif
