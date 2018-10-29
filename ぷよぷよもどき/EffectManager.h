#pragma once
#include<list>
#include"Animation.h"
#include<d3dx9.h>
class Effect
{
public:
	virtual void Update() {}
	virtual void Render() {}
	virtual bool IsFinished() const { return true; }
};

class DeleteEffect:public Effect
{
	static bool s_isAnimationLoaded;
	static IDirect3DTexture9 * s_puyoDeleteTexture;

	static Animation*s_animations[5];

	D3DXVECTOR2 m_position;

	AnimationController*m_controller;

public:
	DeleteEffect();
	void SetPosition(float x ,float y);
	virtual void Update() override;
	virtual void Render() override;
	virtual bool IsFinished() const override;
};

class ComboEffect :public Effect
{
	static bool s_isAnimationLoaded;

	static IDirect3DTexture9 * s_comboTexture;
	D3DXVECTOR2 m_position;

	float m_seconds;
	char m_comboCount;
	//Œ…‚²‚Æ‚É•ª‚¯‚é
	char m_digit[4];
	//‰½Œ…‚©‹L‰¯‚³‚¹‚é
	char m_digitCount;
public:
	ComboEffect(float seconds,char comboCount);
	void SetPosition(float x, float y);
	virtual void Update() override;
	virtual void Render() override;
	virtual bool IsFinished() const override;
};


class EffectManager
{
	std::list<Effect*> m_effectList;

public:
	void AddEffect(Effect*effect);

	void UpdateAllEffects();

	void RenderAllEffects();


};