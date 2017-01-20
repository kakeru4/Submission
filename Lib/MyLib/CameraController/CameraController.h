/*
* @file		CameraController.h
* @brief	CameraController�N���X�w�b�_
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
	* Singleton�p�^�[��
	* ���̂�����֐�
	*/
	static CameraController &GetInstance()
	{
		static CameraController m_CameraController;
		return m_CameraController;
	}

	void Control();

	void CameraRotation();
	

	// ���W�ϊ��֐�
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