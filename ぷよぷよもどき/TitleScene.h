#pragma once
#include"Scene.h"
#include"Graphics.h"
#include"Sound.h"
class TitleScene : public Scene
{
private:
	//���j���[�I���̕ϐ�
	int m_select;
	//�L�[�{�[�h���͂Ɋւ���ϐ�
	bool m_pressRightBefore;
	bool m_pressLeftBefore;
	bool m_pressSpaceBefore;

	//�e�N�X�`���Ɋւ���ϐ�
	IDirect3DTexture9 * m_background;
	IDirect3DTexture9 * m_onlybutton;
	IDirect3DTexture9 * m_onlybuttonafter;
	IDirect3DTexture9 * m_duobutton;
	IDirect3DTexture9 * m_duobuttonafter;
	IDirect3DTexture9 * m_optionbutton;
	IDirect3DTexture9 * m_optionbuttonafter;

	//�T�E���h�Ɋւ���ϐ�
	unsigned short m_titleBGM;
	unsigned short m_cursor;
	unsigned short m_decide;


public:
	TitleScene(const char * name);
	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	virtual void OnStop() override;
	virtual void OnDestroy() override;
};
