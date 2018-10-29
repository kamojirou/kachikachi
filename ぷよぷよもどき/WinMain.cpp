#include "Graphics.h"
#include <stdio.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "OptionScene.h"
#include"Sound.h"
#include"GlobalData.h"
// ゲーム画面の解像度
//  HD:      High Definition  (1280 ×  720)
// FHD: Full High Definition  (1920 × 1080)
const int GameScreenResolutionWidth = 800;
const int GameScreenResolutionHeight = 600;

HWND hWnd;

///////////////////////////////////////////////////////////////////////////////////////////////
//
//  ゲームが始まる直前に1回だけやりたいことを記述しておく関数
//
///////////////////////////////////////////////////////////////////////////////////////////////
void InitializeGame()
{
	//シーンの登録
	auto sceneManager = SceneManager::GetInstance();
	sceneManager->RegisterScene(new TitleScene("タイトル"));
	sceneManager->RegisterScene(new PlayScene("プレイ"));
	sceneManager->RegisterScene(new OptionScene("オプション"));
	sceneManager->RunFirstScene("タイトル");
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// ゲーム世界を画面に描画(レンダリング)する関数
//
///////////////////////////////////////////////////////////////////////////////////////////////
void Render()
{
	// 画面をクリアする (前の画面を消す)
	GetD3DDevice()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);

	// シーンのレンダリングを開始する
	GetD3DDevice()->BeginScene();

	// 半透明合成を有効にする
	 GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	 GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	 GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	 SceneManager::GetInstance()->RenderCurrentScene();

	//
	// ここでゲーム画面の描画を行うこと
	//


	// 現在のマウスカーソルの位置を調べる
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hWnd, &pos);

	// 現在のマウスカーソルの位置を画面に描画する (デバッグ用)
	/*char text[256];
	sprintf_s(text, sizeof(text), "(%4d,%4d)", pos.x, pos.y);
	//DrawTextFormat(0, 0, D3DCOLOR_ARGB(255, 255, 0, 0), text);
	SetWindowText(hWnd, text);
	*/
	// シーンのレンダリングを終了する
	GetD3DDevice()->EndScene();

	// 裏画面(バックバッファ)の内容を表画面(フロントバッファ)に転送する
	GetD3DDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}



///////////////////////////////////////////////////////////////////////////////////////////////
//
// ゲーム内時間を(1/60)秒だけ進める(更新)する関数
//
///////////////////////////////////////////////////////////////////////////////////////////////
void Update()
{
	SceneManager::GetInstance()->UpdateCurrentScene(1.0f / 60);
	SceneManager::GetInstance()->TransitScene();
}




///////////////////////////////////////////////////////////////////////////////////////////////
// ウィンドウプロシージャ
//
//   ・ウィンドウ上で発生したイベントを次々と処理していく関数。
//   ・1つのイベントは対応するメッセージ番号に変換されて送られてくる
//   ・1つのメッセージ番号に対してこの関数が1回呼び出される。
//   ・興味のないメッセージ番号はDefWindowProc()関数に処理されることができる。
//
///////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// ウィンドウが破棄されようとしている時の処理
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		// それ以外の処理
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return (0L);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// エントリーポイント
//
//   ・アプリケーションはこの関数から始まる
//   ・正常終了の場合は0を返すこと
//   ・異常終了の場合は-1を返すこと
//
///////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(
	HINSTANCE hInstance, // 第1引数 : 今回のプロセスのインスタンス番号
	HINSTANCE hPreInst,  // 第2引数 : 前回のプロセスのインスタンス番号
	LPSTR lpszCmdLine,	 // 第3引数 : コマンドライン文字列
	int nCmdShow)		 // 第4引数 : ウィンドウの初期状態
{
	// ① ウィンドウクラスの登録
	//    ウィンドウの企画書を作って、OS(Windows)に提出する。
	//    企画が通ればウィンドウが作れる。
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(wcex));
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbSize = sizeof(wcex);
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hIconSm = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "ウィンドウクラス名を入れる";
	if (!RegisterClassEx(&wcex))
		return FALSE;


	// クライアント領域サイズを指定してウィンドウサイズを計算する関数
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = GameScreenResolutionWidth;
	rect.bottom = GameScreenResolutionHeight;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウサイズ
	int windowW = rect.right - rect.left;
	int windowH = rect.bottom - rect.top;

	// ウィンドウ位置 (センタリング：画面の中央にくるように…)
	int windowX = (GetSystemMetrics(SM_CXSCREEN) - windowW) / 2;
	int windowY = (GetSystemMetrics(SM_CYSCREEN) - windowH) / 2;

	// 企画(ウィンドウクラス)が採用されたので実際にウィンドウを作成する
	hWnd = CreateWindow(
		wcex.lpszClassName,				// 第1引数 : ウィンドウクラス名
		"KachiKachi カチカチ",		// 第2引数 : ウィンドウ名
		WS_OVERLAPPEDWINDOW,			// 第3引数 : ウィンドウスタイル
		windowX,						// 第4引数 : ウィンドウの初期位置(X座標)
		windowY,						// 第5引数 : ウィンドウの初期位置(Y座標)
		windowW,						// 第6引数 : ウィンドウの初期サイズ (横幅)
		windowH,						// 第7引数 : ウィンドウの初期サイズ (高さ)
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// DirectXGraphicsを初期化する
	InitializeDirectXGraphics(hWnd, GameScreenResolutionWidth, GameScreenResolutionHeight);

	StartupSoundSystem();
	GlobalData::Startup();
	SceneManager::Startup();
	// ゲーム開始前のデータを初期化する
	InitializeGame();

	// ウィンドウを可視状態にする
	ShowWindow(hWnd, nCmdShow);

	// ウィンドウを更新する
	UpdateWindow(hWnd);

	// メッセージループ
	//   ・Windowsアプリケーションの心臓部
	//   ・一般アプリケーション向き (Word, Excel等)
	//   ・ゲーム向きではない
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ゲーム世界の描画(レンダリング)
			Render();

			// ゲーム内時間の更新
			Update();
		}
	}
	SceneManager::Shutdown();
	GlobalData::Shutdown();
	ShutdownSoundSystem();

	return (msg.wParam);
}


