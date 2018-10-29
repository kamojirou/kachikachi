#pragma once
#include"Scene.h"
#include"Graphics.h"
#include"Sound.h"
#include"GlobalData.h"

class GlobalData;

class OptionScene :public Scene
{
private:
	//テクスチャに関する変数
	IDirect3DTexture9 * m_background;
	IDirect3DTexture9 * m_background2;
	IDirect3DTexture9 * m_background3;
	IDirect3DTexture9 * m_bg;
	IDirect3DTexture9 * m_bgbutton1;
	IDirect3DTexture9 * m_bgbutton1after;
	IDirect3DTexture9 * m_bgbutton2;
	IDirect3DTexture9 * m_bgbutton2after;
	IDirect3DTexture9 * m_bgbutton3;
	IDirect3DTexture9 * m_bgbutton3after;
	IDirect3DTexture9 * m_BGM;
	IDirect3DTexture9 * m_BGMbutton1;
	IDirect3DTexture9 * m_BGMbutton1after;
	IDirect3DTexture9 * m_BGMbutton2;
	IDirect3DTexture9 * m_BGMbutton2after;
	IDirect3DTexture9 * m_BGMbutton3;
	IDirect3DTexture9 * m_BGMbutton3after;
	IDirect3DTexture9 * m_Volume;
	IDirect3DTexture9 * m_titlebutton;
	IDirect3DTexture9 * m_titlebuttonafter;
	
	//メニュー選択に関する変数
	char m_selectMode;
	char m_menuBackGround;
	char m_menuBGM;
	BGM m_selectBGM;
	BackGround m_selectBackGround;

	//キーボードに関する変数
	bool m_pressRightBefore;
	bool m_pressLeftBefore;
	bool m_pressSpaceBefore;
	bool m_pressUpBefore;
	bool m_pressDownBefore;

	//サウンドに関する変数
	unsigned short m_playBGM;
	unsigned short m_playBGM2;
	unsigned short m_playBGM3;
	unsigned short m_cursor;
	unsigned short m_decide;

public:
	OptionScene(const char * name);
	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	virtual void OnStop() override;
	virtual void OnDestroy() override;
};
