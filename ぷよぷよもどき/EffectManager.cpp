#include "EffectManager.h"
#include"Graphics.h"

bool DeleteEffect::s_isAnimationLoaded = false;
bool ComboEffect::s_isAnimationLoaded = false;

IDirect3DTexture9 * DeleteEffect::s_puyoDeleteTexture = nullptr;
IDirect3DTexture9 * ComboEffect::s_comboTexture = nullptr;

Animation * DeleteEffect::s_animations[5];

AnimationController * animCtrl;

DeleteEffect::DeleteEffect()
{	
	if (!s_isAnimationLoaded)
	{
		s_puyoDeleteTexture = LoadTexture("Assets/Textures/delete.png");
		s_isAnimationLoaded = true;
	}

	Animation * bomb = new Animation();
	for (int i = 0; i < 3; i++)
	{
		bomb->AddFrame(s_puyoDeleteTexture, 97 + 30 * i, 30,30,30, 30);
	}

	animCtrl = new AnimationController();
	animCtrl->ChangeAnimation(bomb);
	animCtrl->Play(1);
}


void DeleteEffect::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void DeleteEffect::Update()
{
	Effect::Update();

	animCtrl->Update(1.0f / 60);
}

void DeleteEffect::Render()
{
	Effect::Render();

	const  Animation::Frame & frame = animCtrl->GetCurrentFrame();
	DrawSprite(m_position.x,m_position.y, frame.sw*1.5f, frame.sh*1.5f, frame.texture, (float)frame.sx, (float)frame.sy, (float)frame.sw, (float)frame.sh);
}

bool DeleteEffect::IsFinished() const
{
	return animCtrl->IsFinished();
}


void EffectManager::AddEffect(Effect * effect)
{
	m_effectList.push_back(effect);
}

void EffectManager::UpdateAllEffects()
{
	auto ite = m_effectList.begin();
	while (ite != m_effectList.end())
	{
		Effect * effect = *ite;
		if (effect->IsFinished())
		{
			ite = m_effectList.erase(ite);
		}
		else
		{
			effect->Update();
			++ite;
		}
	}
}

void EffectManager::RenderAllEffects()
{
	for (Effect * effect : m_effectList)
	{
		effect->Render();
	}
}

ComboEffect::ComboEffect(float seconds, char comboCount)
	: m_seconds(seconds)
	, m_comboCount(comboCount)
	, m_digitCount(0)
{
	if (!s_isAnimationLoaded)
	{
		s_comboTexture = LoadTexture("Assets/Textures/cm_04.png");
	}

	while (comboCount > 0)
	{
		m_digit[m_digitCount] = comboCount % 10;
		comboCount /= 10;
		m_digitCount++;
	}
	/*
	for (int i = 0; i < m_digitCount; i++)
	{
		g->DrawSprite(i*26,48,26.48, s_comboTexture[m_digit[m_digitCount - 1 - i]], 0, 0, 65, 100, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	*/
}

void ComboEffect::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

}

void ComboEffect::Update()
{
	Effect::Update();

	m_seconds -= 1.0f/60;
}

void ComboEffect::Render()
{
	Effect::Render();

	for (int i = 0; i < m_digitCount; i++)
	{
		char value = m_digit[m_digitCount-i-1];

		//コンボ数
		DrawSprite(m_position.x+24*i, m_position.y, 24, 48, s_comboTexture, (float)24*value, 0, 24, 48);
	}

	//「れんさ！」
	DrawSprite(m_position.x+24*m_digitCount, m_position.y+15,128,32, s_comboTexture, 0, 50, 128, 32);

}

bool ComboEffect::IsFinished() const
{
	return m_seconds<0;
}
