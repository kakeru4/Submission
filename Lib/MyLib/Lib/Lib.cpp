/*
* @file		Lib.cpp
* @brief	Libクラス実装
* @author	matsuda
*/

#include "DX9/WindowCreator.h"	
#include "DX9/GraphicsDevice.h"
#include "DX9/InputDevice.h"
#include "DX9/InputKey.h"
#include "DX9/TextureManager.h"
#include "DX9/XFileManager.h"
#include "DX9/VertexManager.h"
#include "DX9/DebugFont.h"
#include "Lib.h"

Lib::Lib()
	: m_pWindowCreator(nullptr)
	, m_pGraphicsDevice(nullptr)
	, m_pInputDevice(nullptr)
	, m_pInputKey(nullptr)
	, m_pTextureManager(nullptr)
	, m_pXFileManager(nullptr)
	, m_pVertexManager(nullptr)
	, m_WinWidth(0)
	, m_WinHeight(0)
{
}

Lib::~Lib()
{
	ReleaseLib();
}

// 初期化関数
void Lib::InitLib(TCHAR*  title, int width, int height, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), bool isFullScreen)
{
	m_WinWidth = width;
	m_WinHeight = height;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	m_pWindowCreator = new WindowCreator(title, width, height);

	m_pGraphicsDevice = &GraphicsDevice::GetInstance();

	m_pWindowCreator->MakeWindow(hInstance, WndProc, isFullScreen);
	m_pGraphicsDevice->InitDevice(m_pWindowCreator->GetHwnd(), isFullScreen, m_WinWidth, m_WinHeight);

	m_pGraphicsDevice->SetRenderState3D();

	m_pInputDevice = &InputDevice::GetInstance();
	m_pInputDevice->InitDinput();
	m_pInputDevice->InitDinputKey(m_pWindowCreator->GetHwnd());
	m_pInputKey = new InputKey();

	m_pTextureManager = new TextureManager();
	m_pXFileManager = new XFileManager();
	m_pVertexManager = new VertexManager();
}

// メモリ開放関数
void Lib::ReleaseLib()
{
	delete m_pVertexManager;
	m_pVertexManager = nullptr;

	delete m_pXFileManager;
	m_pXFileManager = nullptr;

	delete m_pTextureManager;
	m_pTextureManager = nullptr;

	delete m_pInputKey;
	m_pInputKey = nullptr;

	delete m_pWindowCreator;
	m_pWindowCreator = nullptr;
}

// ウィンドウタイプを変える関数
void Lib::ChangeWindowMode()
{
	m_pGraphicsDevice->ChangeDisplayMode();
	m_pWindowCreator->ChangeWindowSize();
}

int Lib::GetWindowWidth()
{
	return m_WinWidth;
}

int Lib::GetWindowHeight()
{
	return m_WinHeight;
}

IDirect3DDevice9* Lib::GetDevice()
{
	return ( m_pGraphicsDevice->GetDevice() );
}

void Lib::StartRender(DWORD FVF)
{
	m_pGraphicsDevice->StartRender(FVF);
}

void Lib::EndRender()
{
	m_pGraphicsDevice->EndRender();
}

void Lib::SetFVF(DWORD FVF)
{
	m_pGraphicsDevice->SetFVF(FVF);
}

void Lib::LoadTex(int key, char* filePath)
{
	m_pTextureManager->Load(key, filePath);
}

void Lib::LoadTexEx(int key, char* filePath, int a, int r, int g, int b, bool size)
{
	m_pTextureManager->LoadEx(key, filePath, a, r, g, b, size);
}

LPDIRECT3DTEXTURE9 Lib::GetTexture(int key)
{
	return m_pTextureManager->GetTex(key);
}

void Lib::CreateVtx(int key, float width, float height, float depth)
{
	m_pVertexManager->CreateVertex(key, width, height, depth);
}

void Lib::SetVtxSize(int key, float width, float height, float depth)
{
	m_pVertexManager->SetSize(key,width,height,depth);
}

void Lib::SetVtxUV(int key, float tuMin, float tuMax, float tvMin, float tvMax)
{
	m_pVertexManager->SetTuTv(key, tuMin, tuMax, tvMin, tvMax);
}

void Lib::SetVtxColor(int key, DWORD color)
{
	m_pVertexManager->SetColor(key, color);
}

void Lib::ScrollUV(int key, float scrollSpeedTu, float scrollSpeedTv)
{
	m_pVertexManager->ScrollUV(key, scrollSpeedTu, scrollSpeedTv);
}

void Lib::DrawXY(int texKey, int vtxKey, float posX, float posY)
{
	m_pVertexManager->Draw2D(vtxKey, m_pTextureManager->GetTex(texKey), posX, posY);
}

void Lib::DrawXYCenterPos(int texKey, int vtxKey, float posX, float posY)
{
	m_pVertexManager->Draw2DCenterPos(vtxKey, m_pTextureManager->GetTex(texKey), posX, posY);
}

void Lib::Draw3DXY(int texKey, int vtxKey)
{
	m_pVertexManager->Draw3DXY(vtxKey, m_pTextureManager->GetTex(texKey));
}

void Lib::Draw3DXYCenterPos(int texKey, int vtxKey)
{
	m_pVertexManager->Draw3DXYCenterPos(vtxKey, m_pTextureManager->GetTex(texKey));
}

void Lib::Draw3DXZ(int texKey, int vtxKey)
{
	m_pVertexManager->Draw3DXZ(vtxKey, m_pTextureManager->GetTex(texKey));
}

void Lib::Draw3DXZCenterPos(int texKey, int vtxKey)
{
	m_pVertexManager->Draw3DXZCenterPos(vtxKey, m_pTextureManager->GetTex(texKey));
}

float Lib::GetVtxWidth(int vtxKey)
{
	return m_pVertexManager->GetVtxWidth(vtxKey);
}

float Lib::GetVtxHeight(int vtxKey)
{
	return m_pVertexManager->GetVtxHeight(vtxKey);
}

float Lib::GetVtxDepth(int vtxKey)
{
	return m_pVertexManager->GetVtxDepth(vtxKey);
}

void Lib::ReleaseTex(int key)
{
	m_pTextureManager->Release(key);
}

void Lib::ReleaseAllTex()
{
	m_pTextureManager->ReleaseALL();
}

void Lib::ReleaseVertex(int key)
{
	m_pVertexManager->Release(key);
}

void Lib::ReleaseAllVertex()
{
	m_pVertexManager->ReleaseALL();
}

void Lib::LoadXFile(int key, LPCTSTR pFilePath)
{
	m_pXFileManager->Load(key, pFilePath);
}

void Lib::DrawXFile(int key)
{
	m_pXFileManager->Draw(key);
}

void Lib::ReleaseXFile(int key)
{
	m_pXFileManager->Release(key);
}

void  Lib::ReleaseAllXFile()
{
	m_pXFileManager->ReleaseALL();
}

void Lib::UpdateDI()
{
	m_pInputKey->UpdateKey();
}

BUTTON_STATE Lib::CheckKey(int DIK, KEYKIND keyName)
{
	BUTTON_STATE state;

	switch(m_pInputKey->CheckKey(DIK, keyName))
	{
	case BTN_ON:
		state = ON;
		break;

	case BTN_OFF:
		state = OFF;
		break;

	case BTN_PUSH:
		state = PUSH;
		break;

	case BTN_RELEASE:
		state = RELEASE;
		break;
	}
	return state;
}

void Lib::DrawDebugFont(std::string text, float posX, float posY)
{
	DebugFont font;
	font.Draw(text.c_str(), D3DXVECTOR2(posX, posY));
}