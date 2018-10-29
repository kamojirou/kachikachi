#include "Animation.h"
#include <cassert>

void Animation::AddFrame(IDirect3DTexture9 * texture, int sx, int sy, int sw, int sh, int time)
{
	Frame frame;
	frame.texture = texture;
	frame.sx = sx;
	frame.sy = sy;
	frame.sw = sw;
	frame.sh = sh;
	frame.time = time;
	m_frames.push_back(frame);
}


int Animation::GetFrameCount() const
{
	return (int)m_frames.size();
}


const Animation::Frame & Animation::GetFrameByIndex(int index) const
{
	return m_frames[index];
}



AnimationController::AnimationController()
	: m_animation(nullptr)
	, m_index(0)
	, m_time(0.0f)
	, m_state(State::Stopped)
	, m_looptimes(0)
	, m_isFinished(false)
{
}


void AnimationController::ChangeAnimation(Animation * animation)
{
	m_animation = animation;
}

void AnimationController::Play(int looptimes)
{
	m_index = 0;
	m_time = 0.0f;
	m_looptimes = looptimes;
	if (m_looptimes != 0)
	{
		m_isFinished = false;
		m_state = State::Playing;
	}
}

void AnimationController::Stop()
{
	m_index = 0;
	m_time = 0.0f;
	m_state = State::Stopped;
}

void AnimationController::Pause()
{
	if (m_state == State::Playing)
	{
		m_state = State::Paused;
	}
}

void AnimationController::Resume()
{
	if (m_state == State::Paused)
	{
		m_state = State::Playing;
	}
}

bool AnimationController::IsFinished() const
{
	return m_isFinished;
}


void AnimationController::Update(float deltaTime)
{
	// アニメーションが未設定
	if (!m_animation)
		return;

	if (m_state != State::Playing)
		return;

	// m_indexコマ目の情報を取得する
	const Animation::Frame & frame = m_animation->GetFrameByIndex(m_index);

	// 累積表示時間 >= コマの持続時間
	if (m_time >= frame.time)
	{
		// まだコマが残っているか？
		if (m_index + 1 < m_animation->GetFrameCount())
		{
			// 次のコマへ
			m_index++;
		}
		else
		{
			if (m_looptimes < 0)
			{
				// 最初のコマに戻る
				m_index = 0;
			}
			else
			{
				assert(m_looptimes != 0);
				if (m_looptimes == 1)
				{
					m_looptimes = 0;
					m_isFinished = true;
					m_state = State::Stopped;
				}
				else
				{
					--m_looptimes;
					// 最初のコマに戻る
					m_index = 0;
				}
			}
		}

		m_time = 0;
	}
	else
	{
		// まだこのコマを表示する
		m_time += 1;
	}
}


const Animation::Frame & AnimationController::GetCurrentFrame() const
{
	return m_animation->GetFrameByIndex(m_index);
}
