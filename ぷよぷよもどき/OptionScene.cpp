#include "OptionScene.h"
#include"Graphics.h"
#include"SceneManager.h"
#include"Sound.h"
#include"GlobalData.h"
OptionScene::OptionScene(const char * name)
	:Scene(name)
{
}

void OptionScene::OnCreate()
{
	//テクスチャの読み込み
	m_background = LoadTexture("Assets/Textures/pkayback.png");
	m_background2 = LoadTexture("Assets/Textures/title.png");
	m_background3 = LoadTexture("Assets/Textures/01m2.png");
	m_bg = LoadTexture("Assets/Textures/bg.png");
	m_bgbutton1 = LoadTexture("Assets/Textures/bg1.png");
	m_bgbutton1after = LoadTexture("Assets/Textures/bg1a.png");
	m_bgbutton2 = LoadTexture("Assets/Textures/bg2.png");
	m_bgbutton2after = LoadTexture("Assets/Textures/bg2a.png");
	m_bgbutton3 = LoadTexture("Assets/Textures/bg3.png");
	m_bgbutton3after = LoadTexture("Assets/Textures/bg3a.png");
	m_BGM = LoadTexture("Assets/Textures/bgm.png");
	m_BGMbutton1 = LoadTexture("Assets/Textures/bgm1.png");
	m_BGMbutton1after = LoadTexture("Assets/Textures/bgm1a.png");
	m_BGMbutton2 = LoadTexture("Assets/Textures/bgm2.png");
	m_BGMbutton2after = LoadTexture("Assets/Textures/bgm2a.png");
	m_BGMbutton3 = LoadTexture("Assets/Textures/bgm3.png");
	m_BGMbutton3after = LoadTexture("Assets/Textures/bgm3a.png");
	m_Volume = LoadTexture("Assets/Textures/volume.png");
	m_titlebutton = LoadTexture("Assets/Textures/titlea.png");
	m_titlebuttonafter = LoadTexture("Assets/Textures/titleb.png");
	//サウンドの読み込み
	m_playBGM = OpenSound("Assets/Audio/BGM2/Option.wav");
	m_playBGM2 = OpenSound("Assets/Audio/BGM2/Option2.wav");
	m_playBGM3 = OpenSound("Assets/Audio/BGM2/Option3.wav");
	m_cursor = OpenSound("Assets/Audio/SE2/cursor2.wav");
	m_decide = OpenSound("Assets/Audio/SE2/Decide2.wav");
}

void OptionScene::OnStart()
{
	//変数の初期化
	m_selectMode = 0;
	m_menuBackGround = 0;
	m_menuBGM= 0;
	m_pressRightBefore = false;
	m_pressLeftBefore = false;
	m_pressSpaceBefore = false;
	m_pressUpBefore = false;
	m_pressDownBefore = false;
	//BGM再生
	PlaySound2(m_playBGM, -1, false);
}

void OptionScene::OnUpdate(float deltaTime)
{	
	//キーボードに関する変数
	bool pressRight = (GetKeyState(VK_RIGHT) & 0x8000) ? true : false;
	bool pressLeft = (GetKeyState(VK_LEFT) & 0x8000) ? true : false;
	bool pressUp = (GetKeyState(VK_UP) & 0x8000) ? true : false;
	bool pressDown = (GetKeyState(VK_DOWN) & 0x8000) ? true : false;
	bool pressSpace = (GetKeyState(VK_SPACE) & 0x8000) ? true : false;
	switch (m_selectMode)
	{
	//背景設定
	case 0:
		//「→」キー
		if (!m_pressRightBefore &&pressRight)
		{
			m_menuBackGround += 1;
			if (m_menuBackGround > 2)
				m_menuBackGround = 0;
			PlaySound2(m_cursor, 1, false);
		}
		//「←」キー
		else if (!m_pressLeftBefore && pressLeft)
		{
			m_menuBackGround -= 1;
			if (m_menuBackGround < 0)
				m_menuBackGround = 2;
			PlaySound2(m_cursor, 1, false);
		}
		//「↓」キー
		else if (!m_pressDownBefore && pressDown)
		{
			m_selectMode += 1;
			if (m_selectMode > 2)
				m_selectMode = 0;
			PlaySound2(m_cursor, 1, false);
		}
		//「↑」キー
		else if (!m_pressUpBefore && pressUp)
		{
			m_selectMode -= 1;
			if (m_selectMode < 0)
				m_selectMode = 2;
			PlaySound2(m_cursor, 1, false);
		}
		break;
	//BGM設定	
	case 1:
		//「→」キー
		if (!m_pressRightBefore &&pressRight)
		{
			m_menuBGM += 1;
			if (m_menuBGM > 2)
				m_menuBGM = 0;
			PlaySound2(m_cursor, 1, false);
			if (m_menuBGM == 0)
			{
				StopSound(m_playBGM2);
				StopSound(m_playBGM3);
				PlaySound2(m_playBGM, -1, false);
			}
			else if (m_menuBGM == 1)
			{
				StopSound(m_playBGM);
				StopSound(m_playBGM3);
				PlaySound2(m_playBGM2, -1, false);
			}
			else if (m_menuBGM == 2)
			{
				StopSound(m_playBGM2);
				StopSound(m_playBGM);
				PlaySound2(m_playBGM3, -1, false);
			}
		}
		//「←」キー
		else if (!m_pressLeftBefore && pressLeft)
		{
			m_menuBGM -= 1;
			if (m_menuBGM < 0)
				m_menuBGM = 2;
			PlaySound2(m_cursor, 1, false);
			if (m_menuBGM == 0)
			{
				StopSound(m_playBGM2);
				StopSound(m_playBGM3);
				PlaySound2(m_playBGM, -1, false);
			}
			else if (m_menuBGM == 1)
			{
				StopSound(m_playBGM);
				StopSound(m_playBGM3);
				PlaySound2(m_playBGM2, -1, false);
			}
			else if (m_menuBGM == 2)
			{
				StopSound(m_playBGM2);
				StopSound(m_playBGM);
				PlaySound2(m_playBGM3, -1, false);
			}
		}
		//「↓」キー
		else if (!m_pressDownBefore && pressDown)
		{
			m_selectMode += 1;
			if (m_selectMode > 2)
				m_selectMode = 0;
			PlaySound2(m_cursor, 1, false);
		}
		//「↑」キー
		else if (!m_pressUpBefore && pressUp)
		{
			m_selectMode -= 1;
			if (m_selectMode < 0)
				m_selectMode = 2;
			PlaySound2(m_cursor, 1, false);

		}
		break;
	//タイトルに戻る
	case 2:
		//「↓」キー
		if (!m_pressDownBefore && pressDown)
		{
			m_selectMode += 1;
			if (m_selectMode > 2)
				m_selectMode = 0;
			PlaySound2(m_cursor, 1, false);
		}
		 //「↑」キー
		 else if (!m_pressUpBefore && pressUp)
		{
			m_selectMode -= 1;
			if (m_selectMode < 0)
				m_selectMode = 2;
			PlaySound2(m_cursor, 1, false);
		}
		//スペースキー
		if (!m_pressSpaceBefore && pressSpace)
		 {
			 m_selectBackGround = (BackGround)m_menuBackGround;
			 m_selectBGM = (BGM)m_menuBGM;
			 GlobalData::GetInstance()->SetBGM(m_selectBGM);
			 GlobalData::GetInstance()->SetBackGround(m_selectBackGround);
			 SceneManager::GetInstance()->ReserveNextScene("タイトル");
			 PlaySound2(m_decide, 1, false);
		}
		break;
}
	m_pressRightBefore = pressRight;
	m_pressLeftBefore = pressLeft;
	m_pressSpaceBefore = pressSpace;
	m_pressUpBefore = pressUp;
	m_pressDownBefore = pressDown;
}

void OptionScene::OnRender()
{	
	//背景
	if (m_menuBackGround == 0)
	DrawSprite(0, 0, 800, 600, m_background, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else if (m_menuBackGround == 1)
	DrawSprite(0, 0, 800, 600, m_background2, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else if (m_menuBackGround == 2)
	DrawSprite(0, 0, 800, 600, m_background3, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	FillRect(20, 60, 760, 480, D3DCOLOR_ARGB(200, 200, 200, 200));
	
	//背景設定
	DrawSprite(0, 60, 200, 60, m_bg, 0, 0,200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	if(m_menuBackGround ==0)
	DrawSprite(70, 120, 200, 60, m_bgbutton1, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
	DrawSprite(70, 120, 200, 60, m_bgbutton1after, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	if (m_menuBackGround == 1)
	DrawSprite(290, 120, 200, 60, m_bgbutton2, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
	DrawSprite(290, 120, 200, 60, m_bgbutton2after, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	if (m_menuBackGround == 2)
	DrawSprite(510,120, 200, 60, m_bgbutton3, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
	DrawSprite(510, 120, 200, 60, m_bgbutton3after, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	
	//BGM設定
	DrawSprite(0, 240, 200, 60, m_BGM, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	if (m_menuBGM == 0)
	DrawSprite(70, 300, 200, 60, m_BGMbutton1, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
	DrawSprite(70, 300, 200, 60, m_BGMbutton1after, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	if (m_menuBGM == 1)
	DrawSprite(290, 300, 200, 60, m_BGMbutton2, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
	DrawSprite(290, 300, 200, 60, m_BGMbutton2after, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	if (m_menuBGM == 2)
	DrawSprite(510, 300, 200, 60, m_BGMbutton3, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
	DrawSprite(510, 300, 200, 60, m_BGMbutton3after, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	//DrawSprite(0, 300, 200, 60, m_Volume, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	
	//タイトル
	if (m_selectMode == 2)
		DrawSprite(510, 480, 200, 60, m_titlebuttonafter, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
		DrawSprite(510, 480, 200, 60, m_titlebutton, 0, 0, 200, 60, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

}

void OptionScene::OnStop()
{
	StopSound(m_playBGM);
	StopSound(m_playBGM2);
	StopSound(m_playBGM3);
}

void OptionScene::OnDestroy()
{
}
