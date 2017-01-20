#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<d3dx9.h>

class Lib;
class Light;
class ObjectManager;
class CameraController;

class GameScene
{
public:
	GameScene();
	~GameScene();

	void Control();
	void Draw();
	bool Run();
	void CameraControl();
private:
	Lib* m_pLib;
	Light* m_pLight;
	ObjectManager* m_pObjectManager;
	CameraController* m_pCameraController;
	bool m_isEnd;
	D3DXVECTOR3 m_CameraPos;
	D3DXVECTOR3 m_LookatPos;
	float m_CameraAngle;
};
#endif