#pragma once
#include <d3d9.h>
#include <vector>

// �A�j���[�V����
class Animation
{
public:
	// 1�R�}
	struct Frame
	{
		IDirect3DTexture9 * texture;	// �ǂ̉摜���g���H
		int sx;		// �����X���W
		int sy;		// �����Y���W
		int sw;		// ����
		int sh;		// ����
		int time;	// �������� (�t���[���P��)
	};

private:
	std::vector<Frame> m_frames;

public:
	// �R�}��ǉ����܂��B
	void AddFrame(IDirect3DTexture9 * texture, int sx, int sy, int sw, int sh, int time);

	// ���R�}�����擾���܂��B
	int GetFrameCount() const;

	// index�Ԗڂ̃R�}�����擾���܂��B
	const Frame & GetFrameByIndex(int index) const;
};


// �A�j���[�V��������N���X
class AnimationController
{
private:
	Animation * m_animation;	// �Đ��������A�j���[�V����
	int m_index;				// �����R�}�ځH
	float m_time;				// ���̃R�}�����t���[���\�������H
	
	enum class State
	{
		Playing,	//�Đ���
		Stopped,	//��~��
		Paused,		//�ꎞ��~��
	};

	State m_state;
	int m_looptimes;
	bool m_isFinished;

public:
	// �R���X�g���N�^
	AnimationController();

	// �A�j���[�V������ύX���܂��B
	void ChangeAnimation(Animation * animation);

	//�A�j���[�V�����̍Đ����܂��B
	// -1:�������[�v	0:�Đ����Ȃ�	1:���Đ�	2:���Đ�	�c	
	void Play(int looptimes);

	//�A�j���[�V�������~���܂��B
	void Stop();

	//�A�j���[�V�����̈ꎞ��~���܂��B
	void Pause();

	//�A�j���[�V�����̈ꎞ��~���������܂��B
	void Resume();

	//�A�j���[�V�������I�����Ă���ꍇ�Atrue��Ԃ�
	bool IsFinished()const;

	// �A�j���[�V�������X�V���܂��B
	void Update(float deltaTime);

	// ���ݕ\�����ׂ��R�}���擾���܂��B
	const Animation::Frame & GetCurrentFrame() const;
};
