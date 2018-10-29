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
	//テクスチャの読み込み
	m_background = LoadTexture("Assets/Textures/background.png");
	m_onlybutton = LoadTexture("Assets/Textures/only.png");
	m_onlybuttonafter = LoadTexture("Assets/Textures/only_after.png");
	m_duobutton = LoadTexture("Assets/Textures/duo.png");
	m_duobuttonafter = LoadTexture("Assets/Textures/duo_after.png");
	m_optionbutton = LoadTexture("Assets/Textures/option.png");
	m_optionbuttonafter = LoadTexture("Assets/Textures/option_after.png");
	//サウンドの読み込み
	m_titleBGM = OpenSound("Assets/Audio/BGM2/title.wav");
	m_cursor = OpenSound("Assets/Audio/SE2/cursor.wav");
	m_decide= OpenSound("Assets/Audio/SE2/Decide.wav");
}

void TitleScene::OnStart()
{
	//変数の初期化
	m_select = 0;
	m_pressRightBefore = false;
	m_pressLeftBefore = false;
	m_pressSpaceBefore = false;
	//BGM再生
	PlaySound2(m_titleBGM, -1, false);
}

void TitleScene::OnUpdate(float deltaTime)
{
	//キーボードに関する変数
	bool pressRight = (GetKeyState(VK_RIGHT) & 0x8000) ? true : false;
	bool pressLeft = (GetKeyState(VK_LEFT) & 0x8000) ? true : false;
	bool pressSpace = (GetKeyState(VK_SPACE) & 0x8000) ? true : false;

	//「→」キー
	if (!m_pressRightBefore &&pressRight)
	{
		m_select += 1;
		if (m_select > 1)
			m_select = 0;
		PlaySound2(m_cursor, 1, false);

	}
	//「←」キー
	else if (!m_pressLeftBefore && pressLeft)
	{
		m_select -= 1;
		if (m_select <0)
			m_select = 1;
		PlaySound2(m_cursor, 1, false);

	}
	//スペースキー
	if (!m_pressSpaceBefore && pressSpace)
	{
		switch (m_select)
		{
			//一人用プレイに移動
		case 0:
			SceneManager::GetInstance()->ReserveNextScene("プレイ");
			PlaySound2(m_decide, 1, false);

			break;
			//二人用プレイに移動(未実装)
		/*case 1:
			SceneManager::GetInstance()->ReserveNextScene("プレイ");
			PlaySound2(m_decide, 1, false);

			break;*/
			//オプションに移動
		case 1:
			SceneManager::GetInstance()->ReserveNextScene("オプション");
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

	//背景
	DrawSprite(0, 0, 800, 600, m_background, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	//一人用ボタン
	if (m_select == 0)
		DrawSprite(70, 420, 200, 60, m_onlybutton, 0, 0, 200, 60);
	else
		DrawSprite(70, 420, 200, 60, m_onlybuttonafter, 0, 0, 200, 60);

	/*//二人用ボタン
	if (m_select == 1)
		DrawSprite(300, 420, 200, 60, m_duobutton, 0, 0, 200, 60);
	else
		DrawSprite(300, 420, 200, 60, m_duobuttonafter, 0, 0, 200, 60);
		*/
	//オプションボタン
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
