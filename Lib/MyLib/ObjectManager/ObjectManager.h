#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <d3dx9.h>
class Chips;
class Sea;
class Fighter;
class Object;


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	void Draw();
	void Control();
	void CameraTransform();
	D3DXVECTOR3 GetCameraPos();
	D3DXVECTOR3 GetLookatPos();
	float GetCameraAngle();
	D3DXVECTOR3 GetChipsPos();
private:
	Chips* m_pChips;
	Fighter* m_pFighter;
	Sea*  m_pSea;
};

#endif