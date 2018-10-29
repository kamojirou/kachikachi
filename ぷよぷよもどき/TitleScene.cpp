#include "TitleScene.h"
#include"Graphics.h"
#include"SceneManager.h"
#include"Sound.h"

TitleScene::TitleScene(const char * name)
	:Scene(name)
{
}

void TitleScene::OnCreate()
{
	//�e�N�X�`���̓ǂݍ���
	m_background = LoadTexture("Assets/Textures/background.png");
	m_onlybutton = LoadTexture("Assets/Textures/only.png");
	m_onlybuttonafter = LoadTexture("Assets/Textures/only_after.png");
	m_duobutton = LoadTexture("Assets/Textures/duo.png");
	m_duobuttonafter = LoadTexture("Assets/Textures/duo_after.png");
	m_optionbutton = LoadTexture("Assets/Textures/option.png");
	m_optionbuttonafter = LoadTexture("Assets/Textures/option_after.png");
	//�T�E���h�̓ǂݍ���
	m_titleBGM = OpenSound("Assets/Audio/BGM2/title.wav");
	m_cursor = OpenSound("Assets/Audio/SE2/cursor.wav");
	m_decide= OpenSound("Assets/Audio/SE2/Decide.wav");
}

void TitleScene::OnStart()
{
	//�ϐ��̏�����
	m_select = 0;
	m_pressRightBefore = false;
	m_pressLeftBefore = false;
	m_pressSpaceBefore = false;
	//BGM�Đ�
	PlaySound2(m_titleBGM, -1, false);
}

void TitleScene::OnUpdate(float deltaTime)
{
	//�L�[�{�[�h�Ɋւ���ϐ�
	bool pressRight = (GetKeyState(VK_RIGHT) & 0x8000) ? true : false;
	bool pressLeft = (GetKeyState(VK_LEFT) & 0x8000) ? true : false;
	bool pressSpace = (GetKeyState(VK_SPACE) & 0x8000) ? true : false;

	//�u���v�L�[
	if (!m_pressRightBefore &&pressRight)
	{
		m_select += 1;
		if (m_select > 1)
			m_select = 0;
		PlaySound2(m_cursor, 1, false);

	}
	//�u���v�L�[
	else if (!m_pressLeftBefore && pressLeft)
	{
		m_select -= 1;
		if (m_select <0)
			m_select = 1;
		PlaySound2(m_cursor, 1, false);

	}
	//�X�y�[�X�L�[
	if (!m_pressSpaceBefore && pressSpace)
	{
		switch (m_select)
		{
			//��l�p�v���C�Ɉړ�
		case 0:
			SceneManager::GetInstance()->ReserveNextScene("�v���C");
			PlaySound2(m_decide, 1, false);

			break;
			//��l�p�v���C�Ɉړ�(������)
		/*case 1:
			SceneManager::GetInstance()->ReserveNextScene("�v���C");
			PlaySound2(m_decide, 1, false);

			break;*/
			//�I�v�V�����Ɉړ�
		case 1:
			SceneManager::GetInstance()->ReserveNextScene("�I�v�V����");
			PlaySound2(m_decide, 1, false);

			break;
		}
	}
	m_pressRightBefore = pressRight;
	m_pressLeftBefore = pressLeft;
	m_pressSpaceBefore = pressSpace;


}

void TitleScene::OnRender()
{

	//�w�i
	DrawSprite(0, 0, 800, 600, m_background, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	//��l�p�{�^��
	if (m_select == 0)
		DrawSprite(70, 420, 200, 60, m_onlybutton, 0, 0, 200, 60);
	else
		DrawSprite(70, 420, 200, 60, m_onlybuttonafter, 0, 0, 200, 60);

	/*//��l�p�{�^��
	if (m_select == 1)
		DrawSprite(300, 420, 200, 60, m_duobutton, 0, 0, 200, 60);
	else
		DrawSprite(300, 420, 200, 60, m_duobuttonafter, 0, 0, 200, 60);
		*/
	//�I�v�V�����{�^��
	if (m_select == 1)
		DrawSprite(530, 420, 200, 60, m_optionbutton, 0, 0, 200, 60);
	else
		DrawSprite(530, 420, 200, 60, m_optionbuttonafter, 0, 0, 200, 60);
}

void TitleScene::OnStop()
{
     //m_background->Release();
	 StopSound(m_cursor);
	 StopSound(m_decide);

	 StopSound(m_titleBGM);
}

void TitleScene::OnDestroy()
{
}
