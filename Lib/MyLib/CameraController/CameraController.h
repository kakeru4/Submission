/*
* @file		CameraController.h
* @brief	CameraControllerクラスヘッダ
* @author	matsuda
*/

#ifndef CameraController_H
#define CameraController_H

#include <d3dx9.h>
#include <math.h>

class Camera;
class ObjectManager;

class CameraController
{
public:
	/*
	* Singletonパターン
	* 実体をつくる関数
	*/
	static CameraController &GetInstance()
	{
		static CameraController m_CameraController;
		return m_CameraController;
	}

	void Control();

	void CameraRotation();
	

	// 座標変換関数
	void TransformView();
	void TransformView(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookPt, float angle);

	~CameraController();
private:
	Camera* m_pCamera;
	ObjectManager* m_pObjectManager;
	D3DXVECTOR3 m_CameraPos;
	D3DXVECTOR3 m_LookatPos;
	float m_CameraAngle;
	float m_ZoomAngle;
	float m_NormalAngle;
	bool m_IsZoom;
	bool m_isNeedUpdate;
	float m_farZ;
	float m_Rad;
	float m_Range;
	float m_Moveabs;
	float m_RotationSpeed;

	CameraController();
};

#endif //CAMERACONTROLLER_H