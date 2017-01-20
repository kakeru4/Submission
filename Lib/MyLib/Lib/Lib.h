/*
* @file		Lib.h
* @brief	Libクラスヘッダ
* @author	matsuda
*/
#ifndef Lib_H
#define Lib_H

#include <windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include "DX9/InputKey.h"

class WindowCreator;
class GraphicsDevice;
class InputDevice;
class InputKey;
class TextureManager;
class XFileManager;
class VertexManager;
class DebugFont;

enum KEYKIND;

#define DIRECT3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 頂点フォーマット
#define USER_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)					// 頂点フォーマット3D

/*DirectInputにおけるボタンの状態*/
enum BUTTON_STATE
{
	ON,				// キーを押した状態が続いている
	OFF,			// キーを離した状態が続いている
	PUSH,			// キーを押す
	RELEASE			// キーを離す
};

/*
*  Facadeパターンのライブラリのクラス
*/
class Lib
{
private:
	/*
	* コンストラクタ.
	* Singltonパターンなのでprivate
	*/
	Lib();

public:

	
	~Lib();

	/*
	* Libの実体を取得する関数<br>
	* Singletonパターン.
	* @return Libクラスのインスタンス
	*/
	static Lib& GetInstance()
	{
		static Lib lib;
		return lib;
	}

	/*
	* 初期化関数.
	* @param[in] title  ウィンドウタイトル
	* @param[in] width  ウィンドウの横幅
	* @param[in] height ウインドウの縦幅
	* @param[in] Wndproc	ウィンドウプロシージャ関数
	* @param[in] isFullScreen  trueならフルスクリーン,falseなら通常
	*/
	void InitLib(TCHAR*  title, int width, int height, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), bool isFullScreen);

	/*メモリ開放関数*/
	void ReleaseLib();

	/*ウィンドウをフルスクリーンかウィンドウサイズに変える関数*/
	void ChangeWindowMode();

	/*ウィンドウの横幅を取得する関数*/
	int GetWindowWidth();

	/*ウィンドウの縦幅を取得する関数*/
	int GetWindowHeight();

	//------------------------------------------------------------------------------------
	//									描画関連関数
	//------------------------------------------------------------------------------------
	/*
	* デバイスを取得する関数.
	* 残すべきか悩んだが、デバイスを取得して方法を残した方がいいという意見が多数だったので残しておく@matsuda
	* @return デバイスのポインタ
	*/
	IDirect3DDevice9* GetDevice();

	/*
	* 描画開始処理関数.
	* @param[in] FVF 頂点フォーマット
	*/
	void StartRender(DWORD FVF = DIRECT3DFVF_CUSTOMVERTEX);

	/*描画終了処理関数*/
	void EndRender();

	/*
	* 頂点フォーマットを設定する関数
	* @param[in] FVF 頂点フォーマット
	*/
	void SetFVF(DWORD FVF);

	//---------------------------------------------------------------------------------------
	//								テクスチャー関連関数
	//---------------------------------------------------------------------------------------
	/*
	* テクスチャーを読み込む関数.
	* @param[in] key		登録するキー、またはID(enumで作成を想定)
	* @param[in] filepath   ファイル名
	*/
	void LoadTex(int key, char* filePath);

	/*
	* テクスチャーを詳細設定して読み込む関数.
	* @param[in] key		登録するキー、またはID(enumで作成を想定)
	* @param[in] filepath   ファイル名
	* @param[in] a			アルファ値  0～255
	* @param[in] r			色のR値 0～255
	* @param[in] g			色のG値 0～255
	* @param[in] b			色のB値 0～255
	* @param[in] size		テクスチャーのサイズが２のべき乗ならtrue,違うならfalse
	*/
	void LoadTexEx(int key, char* filePath, int a, int r, int g, int b, bool size);

	/*
	* テクスチャーへのポインタを取得する関数
	* @param[in] key	登録したID
	*/
	LPDIRECT3DTEXTURE9 GetTexture(int key);

	/*
	* バーテックスを作成する関数.
	* @param[in] key	登録するキー、またはID(enumで作成を想定)
	* @param[in] width	横幅(X軸)
	* @param[in] height 高さ(Y軸)
	* @param[in] depth  奥行(Z軸) デフォルト引数値は0.0f
	*/
	void CreateVtx(int key, float width, float height, float depth = 0.0f);

	/*
	* バーテックスのサイズ変更を行う関数.
	* @param[in] key	登録したキー、またはID
	* @param[in] width	横幅(X軸)
	* @param[in] height 高さ(Y軸)
	* @param[in] depth  奥行(Z軸) デフォルト引数値は0.0f
	*/
	void SetVtxSize(int key,float width, float height, float depth = 0.0f);

	/*
	* バーテックスのUV変更を行う関数.
	* @param[in] key	登録したキー、またはID
	* @param[in] tuMin  tu値の最小値
	* @param[in] tuMax  tu値の最大値
	* @param[in] tvMin  tv値の最小値
	* @param[in] tvax	tv値の最大値
	*/
	void SetVtxUV(int key, float tuMin, float tuMax, float tvMin, float tvMax);

	/*
	* バーテックスの頂点情報における色の変更を行う関数
	* @param[in] key	登録したキー、またはID
	* @param[in] color  色情報(ARGB) 
	*/
	void SetVtxColor(int key, DWORD color);

	/*
	* UVスクロールを行う関数
	* @param[in] key			登録したキー、またはID
	* @param[in] scrollSpeedTu	tuのスクロールの速さ(変化量)
	* @param[in] scrollSpeedTv	tvのスクロールの速さ(変化量)
	*/
	void ScrollUV(int key, float scrollSpeedTu, float scrollSpeedTv);

	/*
	* 2Dの通常描画関数
	* @param[in] texKey	テクスチャーを登録したキー、またはID
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @param[in] posX	x座標
	* @param[in] posY   y座標
	*/
	void DrawXY(int texKey, int vtxKey, float posX, float posY);

	/*
	* 2Dの描画関数(テクスチャーの中心に座標をあわせる)
	* @param[in] texKey	テクスチャーを登録したキー、またはID
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @param[in] posX	x座標
	* @param[in] posY   y座標
	*/
	void DrawXYCenterPos(int texKey, int vtxKey, float posX, float posY);

	/*
	* 3D空間におけるXY平面ポリゴンの通常描画関数<br>
	* @param[in] texKey		テクスチャーを登録したキー、またはID
	* @param[in] vtxKey		バーテックスを登録したキー、またはID
	*/
	void Draw3DXY(int texKey, int vtxKey);

	/*
	* 3D空間におけるXY平面ポリゴンの中心に座標をあわせて描画する関数
	* @param[in] texKey		テクスチャーを登録したキー、またはID
	* @param[in] vtxKey		バーテックスを登録したキー、またはID
	*/
	void Draw3DXYCenterPos(int texKey, int vtxKey);

	/*
	* 3D空間におけるXZ平面ポリゴンの通常描画関数<br>
	* @param[in] texKey	テクスチャーを登録したキー、またはID
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	*/
	void Draw3DXZ(int texKey, int vtxKey);

	/*
	* 3D空間におけるXZ平面ポリゴンの中心に座標をあわせて描画する関数
	* @param[in] texKey	テクスチャーを登録したキー、またはID
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	*/
	void Draw3DXZCenterPos(int texKey, int vtxKey);

	/*
	* バーテックスの横幅を取得する関数.
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @return バーテックスの横幅
	*/
	float GetVtxWidth(int vtxKey);
	
	/*
	* バーテックスの縦幅を取得する関数.
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @return バーテックスの縦幅
	*/
	float GetVtxHeight(int vtxKey);

	/*
	* バーテックスの奥行きを取得する関数.
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @return バーテックスの奥行き
	*/
	float GetVtxDepth(int vtxKey);

	/*
	* テクスチャーを解放する関数
	* @param[in] key	登録したキー、またはID。
	*/
	void ReleaseTex(int key);

	/*現在管理しているすべてのテクスチャーを解放する関数*/
	void ReleaseAllTex();

	/*
	* バーテックスを解放する関数
	* @param[in] key	登録したキー、またはID。
	*/
	void ReleaseVertex(int key);

	/*バーテックスを全て解放する関数*/
	void ReleaseAllVertex();

	//-------------------------------------------------------------------------------------
	//								Xファイル関連関数
	//-------------------------------------------------------------------------------------
	/*
	* Xファイルを読み込む関数.
	* @param[in] key		 登録するキー、またはID(enumで作成を想定)
	* @param[in] pFilepath   ファイル名
	*/
	void LoadXFile(int key, LPCTSTR pFilePath);

	/*
	* Xファイルを描画する関数.
	* @param[in] key	登録したキー、またはID
	*/
	void DrawXFile(int key);

	/*
	* Xファイルを解放する関数.
	* @param[in] key	登録したキー、またはID。
	*/
	void ReleaseXFile(int key);

	/* Xファイルを全て解放する関数*/
	void ReleaseAllXFile();

	//-----------------------------------------------------------------------------------------------------
	//									入力デバイス関連関数
	//-----------------------------------------------------------------------------------------------------

	/*ダイレクトインプットをアップデートする関数*/
	void UpdateDI();

	/*
	* キーの状態を確認する関数<br>
	* 第二引数をなんとか変更したいが、いい案が浮かばずそのまま残しておく@matsuda
	* @param[in] DIK      ダイレクトインプットキー DIK_
	* @param[in] keyName  キーの名前はenumにてA～Zと数字はONE,TWOと英語表記(InputKey.h参照)
	* @return ボタンの状態
	*/
	BUTTON_STATE CheckKey(int DIK, KEYKIND keyName);

	//-------------------------------------------------------------------------------
	//								デバック機能
	//-------------------------------------------------------------------------------
	/*
	* デバック用の文字を表示させる関数.
	* @param[in] text 表示した文字
	* @param[in] posX x座標
	* @param[in] posY y座標
	*/
	void DrawDebugFont(std::string text, float posX, float posY);

private:
	WindowCreator*		m_pWindowCreator;
	GraphicsDevice*		m_pGraphicsDevice;
	InputDevice*		m_pInputDevice;
	InputKey*			m_pInputKey;
	TextureManager*     m_pTextureManager;
	XFileManager*		m_pXFileManager;
	VertexManager*		m_pVertexManager;
	int				    m_WinWidth;			// ウインドウの幅
	int					m_WinHeight;		// ウィンドウの高さ
};

#endif	// Lib_H

