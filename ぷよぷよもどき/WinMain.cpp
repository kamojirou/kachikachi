#include "Graphics.h"
#include <stdio.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "OptionScene.h"
#include"Sound.h"
#include"GlobalData.h"
// �Q�[����ʂ̉𑜓x
//  HD:      High Definition  (1280 �~  720)
// FHD: Full High Definition  (1920 �~ 1080)
const int GameScreenResolutionWidth = 800;
const int GameScreenResolutionHeight = 600;

HWND hWnd;

///////////////////////////////////////////////////////////////////////////////////////////////
//
//  �Q�[�����n�܂钼�O��1�񂾂���肽�����Ƃ��L�q���Ă����֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////
void InitializeGame()
{
	//�V�[���̓o�^
	auto sceneManager = SceneManager::GetInstance();
	sceneManager->RegisterScene(new TitleScene("�^�C�g��"));
	sceneManager->RegisterScene(new PlayScene("�v���C"));
	sceneManager->RegisterScene(new OptionScene("�I�v�V����"));
	sceneManager->RunFirstScene("�^�C�g��");
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// �Q�[�����E����ʂɕ`��(�����_�����O)����֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////
void Render()
{
	// ��ʂ��N���A���� (�O�̉�ʂ�����)
	GetD3DDevice()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);

	// �V�[���̃����_�����O���J�n����
	GetD3DDevice()->BeginScene();

	// ������������L���ɂ���
	 GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	 GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	 GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	 SceneManager::GetInstance()->RenderCurrentScene();

	//
	// �����ŃQ�[����ʂ̕`����s������
	//


	// ���݂̃}�E�X�J�[�\���̈ʒu�𒲂ׂ�
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hWnd, &pos);

	// ���݂̃}�E�X�J�[�\���̈ʒu����ʂɕ`�悷�� (�f�o�b�O�p)
	/*char text[256];
	sprintf_s(text, sizeof(text), "(%4d,%4d)", pos.x, pos.y);
	//DrawTextFormat(0, 0, D3DCOLOR_ARGB(255, 255, 0, 0), text);
	SetWindowText(hWnd, text);
	*/
	// �V�[���̃����_�����O���I������
	GetD3DDevice()->EndScene();

	// �����(�o�b�N�o�b�t�@)�̓��e��\���(�t�����g�o�b�t�@)�ɓ]������
	GetD3DDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}



///////////////////////////////////////////////////////////////////////////////////////////////
//
// �Q�[�������Ԃ�(1/60)�b�����i�߂�(�X�V)����֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////
void Update()
{
	SceneManager::GetInstance()->UpdateCurrentScene(1.0f / 60);
	SceneManager::GetInstance()->TransitScene();
}




///////////////////////////////////////////////////////////////////////////////////////////////
// �E�B���h�E�v���V�[�W��
//
//   �E�E�B���h�E��Ŕ��������C�x���g�����X�Ə������Ă����֐��B
//   �E1�̃C�x���g�͑Ή����郁�b�Z�[�W�ԍ��ɕϊ�����đ����Ă���
//   �E1�̃��b�Z�[�W�ԍ��ɑ΂��Ă��̊֐���1��Ăяo�����B
//   �E�����̂Ȃ����b�Z�[�W�ԍ���DefWindowProc()�֐��ɏ�������邱�Ƃ��ł���B
//
///////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// �E�B���h�E���j������悤�Ƃ��Ă��鎞�̏���
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		// ����ȊO�̏���
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return (0L);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// �G���g���[�|�C���g
//
//   �E�A�v���P�[�V�����͂��̊֐�����n�܂�
//   �E����I���̏ꍇ��0��Ԃ�����
//   �E�ُ�I���̏ꍇ��-1��Ԃ�����
//
///////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(
	HINSTANCE hInstance, // ��1���� : ����̃v���Z�X�̃C���X�^���X�ԍ�
	HINSTANCE hPreInst,  // ��2���� : �O��̃v���Z�X�̃C���X�^���X�ԍ�
	LPSTR lpszCmdLine,	 // ��3���� : �R�}���h���C��������
	int nCmdShow)		 // ��4���� : �E�B���h�E�̏������
{
	// �@ �E�B���h�E�N���X�̓o�^
	//    �E�B���h�E�̊�揑������āAOS(Windows)�ɒ�o����B
	//    ��悪�ʂ�΃E�B���h�E������B
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
	wcex.lpszClassName = "�E�B���h�E�N���X��������";
	if (!RegisterClassEx(&wcex))
		return FALSE;


	// �N���C�A���g�̈�T�C�Y���w�肵�ăE�B���h�E�T�C�Y���v�Z����֐�
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = GameScreenResolutionWidth;
	rect.bottom = GameScreenResolutionHeight;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�T�C�Y
	int windowW = rect.right - rect.left;
	int windowH = rect.bottom - rect.top;

	// �E�B���h�E�ʒu (�Z���^�����O�F��ʂ̒����ɂ���悤�Ɂc)
	int windowX = (GetSystemMetrics(SM_CXSCREEN) - windowW) / 2;
	int windowY = (GetSystemMetrics(SM_CYSCREEN) - windowH) / 2;

	// ���(�E�B���h�E�N���X)���̗p���ꂽ�̂Ŏ��ۂɃE�B���h�E���쐬����
	hWnd = CreateWindow(
		wcex.lpszClassName,				// ��1���� : �E�B���h�E�N���X��
		"KachiKachi �J�`�J�`",		// ��2���� : �E�B���h�E��
		WS_OVERLAPPEDWINDOW,			// ��3���� : �E�B���h�E�X�^�C��
		windowX,						// ��4���� : �E�B���h�E�̏����ʒu(X���W)
		windowY,						// ��5���� : �E�B���h�E�̏����ʒu(Y���W)
		windowW,						// ��6���� : �E�B���h�E�̏����T�C�Y (����)
		windowH,						// ��7���� : �E�B���h�E�̏����T�C�Y (����)
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// DirectXGraphics������������
	InitializeDirectXGraphics(hWnd, GameScreenResolutionWidth, GameScreenResolutionHeight);

	StartupSoundSystem();
	GlobalData::Startup();
	SceneManager::Startup();
	// �Q�[���J�n�O�̃f�[�^������������
	InitializeGame();

	// �E�B���h�E������Ԃɂ���
	ShowWindow(hWnd, nCmdShow);

	// �E�B���h�E���X�V����
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	//   �EWindows�A�v���P�[�V�����̐S����
	//   �E��ʃA�v���P�[�V�������� (Word, Excel��)
	//   �E�Q�[�������ł͂Ȃ�
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
			// �Q�[�����E�̕`��(�����_�����O)
			Render();

			// �Q�[�������Ԃ̍X�V
			Update();
		}
	}
	SceneManager::Shutdown();
	GlobalData::Shutdown();
	ShutdownSoundSystem();

	return (msg.wParam);
}


