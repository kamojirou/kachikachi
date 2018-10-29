#include "Graphics.h"

// DirectX���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Direct3D�f�o�C�X
IDirect3DDevice9* d3dDevice;

// D3DX�t�H���g
ID3DXFont* d3dxFont;

// D3DX�X�v���C�g
ID3DXSprite* d3dxSprite;


IDirect3DDevice9* GetD3DDevice()
{
	return d3dDevice;
}


void InitializeDirectXGraphics(HWND hWnd, unsigned int resolutionWidth, unsigned int resolutionHeight)
{
	// �@ Direct3D�I�u�W�F�N�g���쐬���� (Direct3D : DirectXGraphics�̋���)
	IDirect3D9* d3dObject;
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);

	// �A �v���[���e�[�V�����p�����[�^�[��ݒ肷��
	//    �E�\�����[�h�����߂�  (�E�B���h�E���[�h or �t���X�N���[�����[�h)
	//    �E�Q�[����ʂ̉𑜓x�����߂�
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;									// �E�B���h�E���[�h
	d3dpp.hDeviceWindow = hWnd;								// �J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E
	d3dpp.BackBufferWidth = resolutionWidth;				// �o�b�N�o�b�t�@�̉���
	d3dpp.BackBufferHeight = resolutionHeight;				// �o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				// �t�H�[�}�b�g�͍��̉�ʃ��[�h�ɏ]��	
	d3dpp.BackBufferCount = 1;								// �o�b�N�o�b�t�@�̐�
	d3dpp.EnableAutoDepthStencil = TRUE;					// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;			// �[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				// Direct3D�ɃX���b�v�G�t�F�N�g��C����
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;			// �}���`�T���v�����O�͍s��Ȃ�
	d3dpp.MultiSampleQuality = 0;							// �}���`�T���v�����O�͍s��Ȃ��̂�0
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���̃��t���b�V�����[�g�����̂܂܎g��
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// ���j�^�̐�����A��҂�
	d3dpp.Flags = 0;

	// �B Direct3D�f�o�C�X���쐬����
	if (0 > d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice))
	{
		if (0 > d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &d3dDevice))
		{
			if (0 > d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice))
			{
				MessageBox(nullptr, "Direct3D�̏������Ɏ��s���܂���", "�G���[", MB_OK);
			}
		}
	}

	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// �_���t�H���g
	D3DXCreateFont(
		d3dDevice,
		24,
		0,
		900,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,            /* �o�͐��x */
		DEFAULT_QUALITY,            /* �o�͕i�� */
		DEFAULT_PITCH | FF_SWISS,    /* �t�H���g�s�b�`�ƃt�@�~�� */
		"�l�r �o�S�V�b�N",
		&d3dxFont
	);

	// �t�H���g�p�X�v���C�g�̍쐬
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

	// �摜�≹����ǂݍ���(���[�h����)
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
	// ���_��\���\����
	struct Vertex
	{
		float x, y, z;	// �ʒu(x,y,z)             ���K�{
		float rhw;		// w�̋t��                 ��2D�ł͕K�{
		D3DCOLOR color;	// ���_�J���[(a,r,g,b)     ���C��
		float u, v;		// �e�N�X�`�����W(u,v)     ���C��
	};

	// �摜�̉����ƍ������擾����
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	dx -= 0.5f;
	dy -= 0.5f;

	//�u���_�v���i�[����z��
	Vertex v[6];

	// ����
	v[0].x = dx;
	v[0].y = dy;
	v[0].z = 0.0f;
	v[0].rhw = 1.0f;
	v[0].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[0].u = sx / desc.Width;
	v[0].v = sy / desc.Height;

	// �E��
	v[1].x = dx + dw;
	v[1].y = dy;
	v[1].z = 0.0f;
	v[1].rhw = 1.0f;
	v[1].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].u = (sx + sw) / desc.Width;
	v[1].v = sy / desc.Height;

	// ����
	v[2].x = dx;
	v[2].y = dy + dh;
	v[2].z = 0.0f;
	v[2].rhw = 1.0f;
	v[2].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].u = sx / desc.Width;
	v[2].v = (sy + sh) / desc.Height;

	// �E��
	v[3].x = dx + dw;
	v[3].y = dy;
	v[3].z = 0.0f;
	v[3].rhw = 1.0f;
	v[3].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].u = (sx + sw) / desc.Width;
	v[3].v = sy / desc.Height;

	// �E��
	v[4].x = dx + dw;
	v[4].y = dy + dh;
	v[4].z = 0.0f;
	v[4].rhw = 1.0f;
	v[4].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[4].u = (sx + sw) / desc.Width;
	v[4].v = (sy + sh) / desc.Height;

	// ����
	v[5].x = dx;
	v[5].y = dy + dh;
	v[5].z = 0.0f;
	v[5].rhw = 1.0f;
	v[5].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[5].u = sx / desc.Width;
	v[5].v = (sy + sh) / desc.Height;

	// ���_�ɂǂ�ȏ�񂪊܂܂�Ă���̂���Direct3D�f�o�C�X�ɋ�����K�v������
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// �ǂ̃e�N�X�`����\��t�������̂���Direct3D�f�o�C�X�ɋ�����K�v������
	d3dDevice->SetTexture(0, texture);

	// ���̒��_��`�悵�Ăق����I
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
	// ���_��\���\����
	struct Vertex
	{
		float x, y, z;	// �ʒu(x,y,z)             ���K�{
		float rhw;		// w�̋t��                 ��2D�ł͕K�{
		D3DCOLOR color;	// ���_�J���[(a,r,g,b)     ���C��
		float u, v;		// �e�N�X�`�����W(u,v)     ���C��
	};

	// �摜�̉����ƍ������擾����
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

	//���_�z��
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
	// ���_��\���\����
	struct Vertex
	{
		float x, y, z;	// �ʒu(x,y,z)             ���K�{
		float rhw;		// w�̋t��                 ��2D�ł͕K�{
		D3DCOLOR color;	// ���_�J���[(a,r,g,b)     ���C��
		float u, v;		// �e�N�X�`�����W(u,v)     ���C��
	};

	// �摜�̉����ƍ������擾����
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

	//���_�z��
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

	// ��]����

	// ��]���̈ʒu (��ʍ���������)
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
	// ���_��\���\����
	struct Vertex
	{
		float x, y, z;	// �ʒu(x,y,z)             ���K�{
		float rhw;		// w�̋t��                 ��2D�ł͕K�{
		D3DCOLOR color;	// ���_�J���[(a,r,g,b)     ���C��
	};

	dx -= 0.5f;
	dy -= 0.5f;

	const float x0 = dx;
	const float y0 = dy;
	const float x1 = dx + dw;
	const float y1 = dy + dh;

	//���_�z��
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


// ��ʂɕ������`�悷��֐�
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



