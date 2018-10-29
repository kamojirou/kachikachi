#pragma once
#include"Scene.h"
#include"Graphics.h"
#include"EffectManager.h"
#include <vector>

enum class PuyoColor : char
{
	Red=0,
	Green,
	Blue,
	Yellow,
	Purple,
	Obstacle,//���ז��Ղ�
	Empty
};

struct PuyoGroup
{
	//�Ղ�̏��
	/*
	������
	������
	������
	*/

	/*
	[0][0]	[0][1]	[0][2]			[2][0]	[1][0]	[0][0]
	[1][0]	[1][1]	[1][2]			[2][1]	[1][1]	[0][1]
	[2][0]	[2][1]	[2][2]			[2][2]	[1][2]	[0][2]

									[+2][+0] [+1][-1] [+0][-2]
									[-1][-1] [+0][+0] [-1][-1]
									[-0][+2] [-1][+1] [-2][+0]
	�E��]							����]
	[0][2] <- [0][0]				[2][0] <- [0][0]
	[1][2] <- [0][1]				[1][0] <- [0][1]
	[2][2] <- [0][2]				[0][0] <- [0][2]
	[0][1] <- [1][0]				[2][1] <- [1][0]
	[1][1] <- [1][1]				[1][1] <- [1][1]
	[2][1] <- [1][2]				[0][1] <- [1][2]
	[0][0] <- [2][0]				[2][2] <- [2][0]
	[1][0] <- [2][1]				[1][2] <- [2][1]
	[2][0] <- [2][2]				[0][2] <- [2][2]
	[x][2-y] <- [y][x]				[2-x][y] <- [y][x]

	*/
	PuyoColor puyo[3][3];

	//4���̂Ղ�(�ł��Ղ�)���ǂ�������
	bool big;

	//�t�B�[���h��������̃s�N�Z���P�ʂ̈ʒu
	float x;
	float y;

	//�Ղ�̌�
	int num;

	// �z�u�p�^�[��
	//    0            1           2           3           4           5
	//	������		������	 	 ������ 	 ������ 	 ������ 	 ������
	//	������		������	 	 ������ 	 ������ 	 ������ 	 ������
	//	������		������	 	 ������ 	 ������ 	 ������ 	 ������
	int pattern;

	//�E�ɉ���]���Ă��邩
	int rotation;
};

// �����Ă���Ղ���
struct FloatingPuyo
{
	PuyoColor color;
	float x;
	float y;
	float vx;
	float vy;

};

enum class PlayState
{
	//�v���C���[������\�ȏ��
	Controllable,
	//�Ղ悪�Ȃ����ď����Ă�����
	DeleteAnimation,
	//�����Ă���Ղ悪�������Ă�����
	DropFloatings,
	//�Ղ悪�Q�[���I�[�o�[���C���ŏ����Ȃ��������
	GameOver
};

struct Position
{
	int x;
	int y;
};

class PlayScene :public Scene
{
private:
	//�e�N�X�`���Ɋւ���ϐ�
	IDirect3DTexture9* background1;
	IDirect3DTexture9* background2;
	IDirect3DTexture9* background3;
	IDirect3DTexture9* backgroundfield;
	IDirect3DTexture9* puyopuyo;
	IDirect3DTexture9* puyogroup;
	IDirect3DTexture9* nextcercle;
	IDirect3DTexture9* nextcercle2;
	IDirect3DTexture9* next;
	IDirect3DTexture9* win;
	IDirect3DTexture9* bar;
	IDirect3DTexture9* score;
	IDirect3DTexture9* highscore;
	IDirect3DTexture9* combo;
	IDirect3DTexture9* maxcombo;
	IDirect3DTexture9* scorenumber;
	IDirect3DTexture9* rule;
	IDirect3DTexture9* gameover;
	//�T�E���h�Ɋւ���ϐ�
	unsigned short m_playBGM1;
	unsigned short m_playBGM2;
	unsigned short m_playBGM3;
	unsigned short m_rotateSE;
	unsigned short m_moveSE;
	unsigned short m_dropSE;
	unsigned short m_bombSE;

	//�Ղ�Ɋւ���ϐ�
	PuyoGroup m_currGroup;
	PuyoGroup m_nextGroup;
	PuyoGroup m_secondGroup;

	//���쏈���Ɋւ���ϐ�
	bool m_pressRightBefore;
	bool m_pressLeftBefore;
	bool m_pressUpBefore;
	bool m_pressDownBefore;
	bool m_pressRight;
	bool m_pressLeft;
	bool m_pressUp;
	bool m_pressDown;
	bool m_pressSpace;
	bool m_pressSpaceBefore;

	//����]
	bool m_pressABefore;
	bool m_pressA;
	//�E��]
	bool m_pressDBefore;
	bool m_pressD;

	//�t�B�[���h�̍����i�s�N�Z���P�ʁj
	static const int FIELD_OFFSET_X = 70;
	static const int FIELD_OFFSET_Y = 10;

	//�t�B�[���h�̃}�X��
	static const int FIELD_NUM_X = 6;
	static const int FIELD_NUM_Y = 14;
	//�l�N�X�g�Ղ�̈ʒu
	static const int NEXT_POS_X = 205;
	static const int NEXT_POS_Y = 90;
	//�Z�J���h�Ղ�̈ʒu
	static const int SECOND_POS_X = 300;
	static const int SECOND_POS_Y = 160;

	//�Ղ�摜�̐F�̊Ԋu��
	static const int PUYO_IMAGE_WIDTH = 94;

	//�Ղ����̑傫�� ��40�@����40
	static const int PUYO_SIZE =40;

	//�����Ă���Ղ�̉����x(������)
	static const float FLOATING_PUYO_AX;
	static const float FLOATING_PUYO_AY;

	//�t�B�[���h�̔z��
	PuyoColor m_field[FIELD_NUM_Y][FIELD_NUM_X];
	// �T���ς݃t���O
	bool m_found[FIELD_NUM_Y][FIELD_NUM_X];

	//������Ղ�z��
	int m_deletablePuyoCount;
	Position m_deletablePuyos[FIELD_NUM_X*FIELD_NUM_Y];

	//�����Ă���Ղ�̌�
	int m_floatingCount;
	FloatingPuyo m_floatigs[FIELD_NUM_X*FIELD_NUM_Y];

	//������
	PlayState m_playState;

	//�G�t�F�N�g
	EffectManager * m_effectManager;

	//�A����
	char m_comboCount;
	char m_maxcomboCount;

	//�X�R�A
	int m_score;
	int m_highscore;

public:

	PlayScene(const char * name);
	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	virtual void OnStop() override;
	virtual void OnDestroy() override;

private:
	//���삵�Ă���Ղ�̕`��Ɋւ���ւ���
	void RenderPuyoGroup(const PuyoGroup*group);
	//������I�����Ղ�Ɋւ���֐�
	void FixGroupOnField(const PuyoGroup*group);
	//�Ղ悪�u����ꏊ��T������֐�
	bool Putable(const PuyoGroup*group);
	//�����Ă���Ղ��T������֐�
	bool FindFloatingPuyo();
	//�����Ă���Ղ�𗎉�������֐�
	bool DropFloatingPuyo();
	//�������Ղ�̗�����̕`��Ɋւ���֐�
	void RenderFloatingPuyo();
	//void RenderNextPuyoGroup(const PuyoGroup * group);
	//������Ղ��T������֐�
	bool FindDeletablePuyo();
	//�Q�[���I�[�o�[���C����̂Ղ��������֐�
	bool FindGameOverLine();
	//�����Ă���Ղ悪�u����ꏊ��T������֐�
	bool Putableone(const FloatingPuyo*puyo);
	//���삵�Ă���Ղ���E��]������֐�
	void RotateRight(PuyoGroup*group);
	//���삵�Ă���Ղ������]������֐�
	void RotateLeft(PuyoGroup*group);
	//�����F�̂Ղ悪�Ȃ����Ă��邩�ǂ������ׂ�֐�
	void FindLinkedPuyo(PuyoColor color, int x,int y, std::vector<Position> & linked);
	//�Ղ����������
	void DeletePuyos();
	//�X�R�A��`�悷��֐�
	void RenderScore(int x, int y, int score);
	//�A����`�悷��֐�
	void RenderMaxCombo(int x, int y, int combo);
};