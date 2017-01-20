#ifndef CHIPS_H
#define CHIPS_H

#include "../Object/Object.h"

class Chips:public Object
{
public:
	Chips(D3DXVECTOR3* pos);
	virtual ~Chips();
	virtual void Control();
	virtual void Draw();
	void CameraTransWorld(float radius);
	D3DXVECTOR3 GetCameraPos();
	D3DXVECTOR3 GetLookatPos();
	float GetCameraAngle();
	D3DXVECTOR3 GetChipsPos();
private:
	D3DXVECTOR3 m_ChipsPos;
	D3DXVECTOR3				m_CameraPos;            //カメラの座標
	D3DXVECTOR3				m_LookatPos;            //注視点の座標
	float                   m_CameraAngle;
	D3DXMATRIX				m_CameraRotation;
};
#endif
