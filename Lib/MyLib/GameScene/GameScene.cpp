#include"GameScene.h"
#include"../CameraController/CameraController.h"
#include"../Light/Light.h"
#include"../Lib/Lib.h"
#include"../ObjectManager/ObjectManager.h"
#include"../CollisionManager/CollisionManager.h"

GameScene::GameScene()
	:m_pLib(&Lib::GetInstance())
	, m_pObjectManager(new ObjectManager())
	, m_pCameraController(&CameraController::GetInstance())
{
	m_pLight = new Light(Lib::GetInstance().GetDevice(), D3DXVECTOR3{ 0, 0, 0 });
}

GameScene::~GameScene()
{
	delete m_pLight;
	delete m_pObjectManager;
}

void GameScene::Control()
{
	CollisionManager::GetInstance().ClearData();
	//m_pObjectManager->CameraTransform();
	//CameraControl();
	CameraController::GetInstance().Control();
	m_pObjectManager->Control();
	

	CollisionManager::GetInstance().CheckCollision();
}

void GameScene::Draw()
{
	Lib::GetInstance().DrawDebugFont("←→: 物体の左右移動", 10, 10);
	Lib::GetInstance().DrawDebugFont("↑: 物体の奥行き方向移動", 10, 30);
	Lib::GetInstance().DrawDebugFont("↓: 物体の手前方向移動", 10, 50);
	Lib::GetInstance().DrawDebugFont("W,S,A,D: カメラの左右上下移動", 10, 70);
	Lib::GetInstance().DrawDebugFont("1: ズームイン", 10, 90);
	Lib::GetInstance().DrawDebugFont("P: 別視点のカメラ切り替え", 10, 110);
	CameraController::GetInstance().TransformView();
	m_pObjectManager->Draw();
}

bool GameScene::Run()
{
	m_pLib->UpdateDI();

	Control();

	m_pLib->StartRender(USER_VERTEX_FVF);

	Lib::GetInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	Draw();

	m_pLib->EndRender();

	return m_isEnd;
}

void GameScene::CameraControl()
{
	/*if (Lib::GetInstance().CheckKey(DIK_A, A) == ON)
	{
		m_CameraPos.x -= 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_D, D) == ON)
	{
		m_CameraPos.x += 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_W, W) == ON)
	{
		m_CameraPos.y -= 10;
	}

	if (Lib::GetInstance().CheckKey(DIK_S, S) == ON)
	{
		m_CameraPos.y += 10;
	}*/

}