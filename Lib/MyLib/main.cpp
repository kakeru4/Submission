#include <windows.h>
#include <iostream>
#include <crtdbg.h>
#include "GameScene/GameScene.h"
#include "Lib/Lib.h"


#define WINDOW_MODE						// ウィンドウモード(通常)

#define WINDOW_TITLE TEXT("課題")		// ウィンドウタイトル
#define CLIENT_SIZE_W 1600				// クライアントサイズの幅
#define CLIENT_SIZE_H 900 				// クライアントサイズの高さ
#define GAME_FPS (1000 / 60)			// ゲームFPS

// プロシージャ関数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg;

	/*-------------------------------------------------------------------*/
	//				         ウィンドウ生成
	/*-------------------------------------------------------------------*/	
#ifdef WINDOW_MODE		//	ウィンドウモード(通常)
	Lib::GetInstance().InitLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, false);
#else					//　フルスクリーンモード
	Lib::Instance().InitLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, true);
#endif

	GameScene* pGameScene = new GameScene();

	//-------------------------------------------------------------------//
	//						メッセージループ
	//-------------------------------------------------------------------//
	//timeBeginPeriod(1);
	DWORD currentTime;						// 現在の時間
	DWORD oldTime = timeGetTime();			// 前の時間

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

// ウインドウプロシージャ関数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		int answer = MessageBox(hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO);
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
			int answer = MessageBox(hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO);
			if (answer == IDYES)
			{
				PostQuitMessage(0);
				return 0;
			}
		}
		break;
		}
		break;

	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch ((CHAR)wparam)
		{
		case VK_RETURN:     // Alt + Enterを押すとウィンドウ切り替え
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