#include "Graphics.h"

// DirectXライブラリのリンク
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Direct3Dデバイス
IDirect3DDevice9* d3dDevice;

// D3DXフォント
ID3DXFont* d3dxFont;

// D3DXスプライト
ID3DXSprite* d3dxSprite;


IDirect3DDevice9* GetD3DDevice()
{
	return d3dDevice;
}


void InitializeDirectXGraphics(HWND hWnd, unsigned int resolutionWidth, unsigned int resolutionHeight)
{
	// ① Direct3Dオブジェクトを作成する (Direct3D : DirectXGraphicsの旧名)
	IDirect3D9* d3dObject;
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);

	// ② プレゼンテーションパラメーターを設定する
	//    ・表示モードを決める  (ウィンドウモード or フルスクリーンモード)
	//    ・ゲーム画面の解像度を決める
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;									// ウィンドウモード
	d3dpp.hDeviceWindow = hWnd;								// カバーウィンドウ＝アプリケーションのウィンドウ
	d3dpp.BackBufferWidth = resolutionWidth;				// バックバッファの横幅
	d3dpp.BackBufferHeight = resolutionHeight;				// バックバッファの高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				// フォーマットは今の画面モードに従う	
	d3dpp.BackBufferCount = 1;								// バックバッファの数
	d3dpp.EnableAutoDepthStencil = TRUE;					// Direct3Dに深度バッファの管理を任せる
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;			// 深度バッファのフォーマット（通常はこの値で問題ない）
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				// Direct3Dにスワップエフェクトを任せる
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;			// マルチサンプリングは行わない
	d3dpp.MultiSampleQuality = 0;							// マルチサンプリングは行わないので0
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// 今のリフレッシュレートをそのまま使う
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// モニタの垂直回帰を待つ
	d3dpp.Flags = 0;

	// ③ Direct3Dデバイスを作成する
	if (0 > d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice))
	{
		if (0 > d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &d3dDevice))
		{
			if (0 > d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice))
			{
				MessageBox(nullptr, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
			}
		}
	}

	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 論理フォント
	D3DXCreateFont(
		d3dDevice,
		24,
		0,
		900,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,            /* 出力精度 */
		DEFAULT_QUALITY,            /* 出力品質 */
		DEFAULT_PITCH | FF_SWISS,    /* フォントピッチとファミリ */
		"ＭＳ Ｐゴシック",
		&d3dxFont
	);

	// フォント用スプライトの作成
	D3DXCreateSprite(d3dDevice, &d3dxSprite);
}


IDirect3DTexture9* LoadTexture(const char * path)
{
	unsigned int width, height;
	return LoadTextureEx(path, &width, &height);
}


IDirect3DTexture9 * LoadTextureEx(const char * path, unsigned int * width, unsigned int * height)
{
	D3DXIMAGE_INFO info;

	IDirect3DTexture9* texture;

	// 画像や音声を読み込む(ロードする)
	D3DXCreateTextureFromFileEx(
		GetD3DDevice(),
		path,
		0,
		0,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		&info,
		nullptr,
		&texture
	);

	*width = info.Width;
	*height = info.Height;

	return texture;
}

/*
void DrawSprite(float dx, float dy, float dw, float dh, IDirect3DTexture9* texture, float sx, float sy, float sw, float sh)
{
	// 頂点を表す構造体
	struct Vertex
	{
		float x, y, z;	// 位置(x,y,z)             ※必須
		float rhw;		// wの逆数                 ※2Dでは必須
		D3DCOLOR color;	// 頂点カラー(a,r,g,b)     ※任意
		float u, v;		// テクスチャ座標(u,v)     ※任意
	};

	// 画像の横幅と高さを取得する
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	dx -= 0.5f;
	dy -= 0.5f;

	//「頂点」を格納する配列
	Vertex v[6];

	// 左上
	v[0].x = dx;
	v[0].y = dy;
	v[0].z = 0.0f;
	v[0].rhw = 1.0f;
	v[0].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[0].u = sx / desc.Width;
	v[0].v = sy / desc.Height;

	// 右上
	v[1].x = dx + dw;
	v[1].y = dy;
	v[1].z = 0.0f;
	v[1].rhw = 1.0f;
	v[1].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].u = (sx + sw) / desc.Width;
	v[1].v = sy / desc.Height;

	// 左下
	v[2].x = dx;
	v[2].y = dy + dh;
	v[2].z = 0.0f;
	v[2].rhw = 1.0f;
	v[2].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].u = sx / desc.Width;
	v[2].v = (sy + sh) / desc.Height;

	// 右上
	v[3].x = dx + dw;
	v[3].y = dy;
	v[3].z = 0.0f;
	v[3].rhw = 1.0f;
	v[3].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].u = (sx + sw) / desc.Width;
	v[3].v = sy / desc.Height;

	// 右下
	v[4].x = dx + dw;
	v[4].y = dy + dh;
	v[4].z = 0.0f;
	v[4].rhw = 1.0f;
	v[4].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[4].u = (sx + sw) / desc.Width;
	v[4].v = (sy + sh) / desc.Height;

	// 左下
	v[5].x = dx;
	v[5].y = dy + dh;
	v[5].z = 0.0f;
	v[5].rhw = 1.0f;
	v[5].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[5].u = sx / desc.Width;
	v[5].v = (sy + sh) / desc.Height;

	// 頂点にどんな情報が含まれているのかをDirect3Dデバイスに教える必要がある
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// どのテクスチャを貼り付けたいのかをDirect3Dデバイスに教える必要がある
	d3dDevice->SetTexture(0, texture);

	// この頂点を描画してほしい！
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, 28);
}
*/

void Swap(float & a, float & b)
{
	float temp = a;
	a = b;
	b = temp;
}


void DrawSprite(float dx, float dy, float dw, float dh, IDirect3DTexture9* texture, float sx, float sy, float sw, float sh, D3DCOLOR color, int flags)
{
	// 頂点を表す構造体
	struct Vertex
	{
		float x, y, z;	// 位置(x,y,z)             ※必須
		float rhw;		// wの逆数                 ※2Dでは必須
		D3DCOLOR color;	// 頂点カラー(a,r,g,b)     ※任意
		float u, v;		// テクスチャ座標(u,v)     ※任意
	};

	// 画像の横幅と高さを取得する
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	dx -= 0.5f;
	dy -= 0.5f;

	const float x0 = dx;
	const float y0 = dy;
	const float x1 = dx + dw;
	const float y1 = dy + dh;
	const float u0 = sx / desc.Width;
	const float v0 = sy / desc.Height;
	const float u1 = (sx + sw) / desc.Width;
	const float v1 = (sy + sh) / desc.Height;

	//頂点配列
	Vertex v[4] =
	{
		{ x0, y0, 0.0f, 1.0f, color, u0, v0, },
		{ x1, y0, 0.0f, 1.0f, color, u1, v0, },
		{ x0, y1, 0.0f, 1.0f, color, u0, v1, },
		{ x1, y1, 0.0f, 1.0f, color, u1, v1, },
	};

	if (flags & DS_FLIP_X)
	{
		Swap(v[0].u, v[1].u);
		Swap(v[2].u, v[3].u);
	}

	if (flags & DS_FLIP_Y)
	{
		Swap(v[0].v, v[2].v);
		Swap(v[1].v, v[3].v);
	}

	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	d3dDevice->SetTexture(0, texture);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex));
}


void DrawSpriteEx(float dx, float dy, float dw, float dh, float ox, float oy, float radians, IDirect3DTexture9 * texture, float sx, float sy, float sw, float sh, D3DCOLOR color, int flags)
{
	// 頂点を表す構造体
	struct Vertex
	{
		float x, y, z;	// 位置(x,y,z)             ※必須
		float rhw;		// wの逆数                 ※2Dでは必須
		D3DCOLOR color;	// 頂点カラー(a,r,g,b)     ※任意
		float u, v;		// テクスチャ座標(u,v)     ※任意
	};

	// 画像の横幅と高さを取得する
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	dx -= 0.5f;
	dy -= 0.5f;

	const float x0 = dx;
	const float y0 = dy;
	const float x1 = dx + dw;
	const float y1 = dy + dh;
	const float u0 = sx / desc.Width;
	const float v0 = sy / desc.Height;
	const float u1 = (sx + sw) / desc.Width;
	const float v1 = (sy + sh) / desc.Height;

	//頂点配列
	Vertex v[4] =
	{
		{ x0, y0, 0.0f, 1.0f, color, u0, v0, },
		{ x1, y0, 0.0f, 1.0f, color, u1, v0, },
		{ x0, y1, 0.0f, 1.0f, color, u0, v1, },
		{ x1, y1, 0.0f, 1.0f, color, u1, v1, },
	};

	if (flags & DS_FLIP_X)
	{
		Swap(v[0].u, v[1].u);
		Swap(v[2].u, v[3].u);
	}

	if (flags & DS_FLIP_Y)
	{
		Swap(v[0].v, v[2].v);
		Swap(v[1].v, v[3].v);
	}

	// 回転処理

	// 回転軸の位置 (画面左上隅からの)
	const float rotationAxisX = dx + dw * ox;
	const float rotationAxisY = dy + dh * oy;
	const float sin = sinf(radians);
	const float cos = cosf(radians);
	for (int i = 0; i < 4; i++)
	{
		const float x = v[i].x - rotationAxisX;
		const float y = v[i].y - rotationAxisY;
		const float rx = x * cos + y * (-sin);
		const float ry = x * sin + y * cos;
		v[i].x = rx + rotationAxisX;
		v[i].y = ry + rotationAxisY;
	}

	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	d3dDevice->SetTexture(0, texture);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex));
}


void FillRect(float dx, float dy, float dw, float dh, D3DCOLOR color)
{
	// 頂点を表す構造体
	struct Vertex
	{
		float x, y, z;	// 位置(x,y,z)             ※必須
		float rhw;		// wの逆数                 ※2Dでは必須
		D3DCOLOR color;	// 頂点カラー(a,r,g,b)     ※任意
	};

	dx -= 0.5f;
	dy -= 0.5f;

	const float x0 = dx;
	const float y0 = dy;
	const float x1 = dx + dw;
	const float y1 = dy + dh;

	//頂点配列
	const Vertex v[4] =
	{
		{ x0, y0, 0.0f, 1.0f, color, },
		{ x1, y0, 0.0f, 1.0f, color, },
		{ x0, y1, 0.0f, 1.0f, color, },
		{ x1, y1, 0.0f, 1.0f, color, },
	};

	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->SetTexture(0, nullptr);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex));
}


// 画面に文字列を描画する関数
void DrawTextFormat(int x, int y, D3DCOLOR color, const char * text)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = 1280;
	rect.bottom = 720;

	d3dxSprite->Begin(D3DXSPRITE_ALPHABLEND);
	d3dxFont->DrawTextA(d3dxSprite, text, -1, &rect, DT_LEFT, color);
	d3dxSprite->End();
}



