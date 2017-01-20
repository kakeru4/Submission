#include <windows.h>
#include <iostream>
#include <crtdbg.h>
#include "GameScene/GameScene.h"
#include "Lib/Lib.h"


#define WINDOW_MODE						// �E�B���h�E���[�h(�ʏ�)

#define WINDOW_TITLE TEXT("�ۑ�")		// �E�B���h�E�^�C�g��
#define CLIENT_SIZE_W 1600				// �N���C�A���g�T�C�Y�̕�
#define CLIENT_SIZE_H 900 				// �N���C�A���g�T�C�Y�̍���
#define GAME_FPS (1000 / 60)			// �Q�[��FPS

// �v���V�[�W���֐�
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

// �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg;

	/*-------------------------------------------------------------------*/
	//				         �E�B���h�E����
	/*-------------------------------------------------------------------*/	
#ifdef WINDOW_MODE		//	�E�B���h�E���[�h(�ʏ�)
	Lib::GetInstance().InitLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, false);
#else					//�@�t���X�N���[�����[�h
	Lib::Instance().InitLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, true);
#endif

	GameScene* pGameScene = new GameScene();

	//-------------------------------------------------------------------//
	//						���b�Z�[�W���[�v
	//-------------------------------------------------------------------//
	//timeBeginPeriod(1);
	DWORD currentTime;						// ���݂̎���
	DWORD oldTime = timeGetTime();			// �O�̎���

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			currentTime = timeGetTime();
			if (currentTime - oldTime >= GAME_FPS)
			{
				if (pGameScene->Run())
				{
					break;
				}
				oldTime = timeGetTime();
			}
		}
	}
	//timeEndPeriod(1);

	delete pGameScene;
	Lib::GetInstance().ReleaseLib();

	return (INT)msg.wParam;
}

// �E�C���h�E�v���V�[�W���֐�
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		int answer = MessageBox(hwnd, TEXT("�I���܂����H"), TEXT("�I��"), MB_YESNO);
		if (answer == IDYES)
		{
			PostQuitMessage(0);
			return  0;
		}
	}

	break;
	case WM_KEYDOWN:
		switch ((CHAR)wparam)
		{
		case VK_ESCAPE:
		{
			int answer = MessageBox(hwnd, TEXT("�I���܂����H"), TEXT("�I��"), MB_YESNO);
			if (answer == IDYES)
			{
				PostQuitMessage(0);
				return 0;
			}
		}
		break;
		}
		break;

	case WM_SYSKEYDOWN:     // Alt + ����L�[�̏����Ɏg��
		switch ((CHAR)wparam)
		{
		case VK_RETURN:     // Alt + Enter�������ƃE�B���h�E�؂�ւ�
			Lib::GetInstance().ChangeWindowMode();
			break;
		default:
			break;
		}
		break;

	case WM_ACTIVATE:
		switch ((CHAR)wparam)
		{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:

			break;
		}
	}
	return  DefWindowProc(hwnd, message, wparam, lparam);
}