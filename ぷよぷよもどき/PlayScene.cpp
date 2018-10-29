#include "PlayScene.h"
#include"Graphics.h"
#include"Scene.h"
#include"Sound.h"
#include"GlobalData.h"
#include"SceneManager.h"

//�Ղ�ړ��̉����x�ϐ�
const float PlayScene::FLOATING_PUYO_AX = 0.0f;
const float PlayScene::FLOATING_PUYO_AY = 0.5f;

//�Ղ搶���̊֐�
void GeneratePuyoGroup(PuyoGroup*group)
{
	//������
	group->x = 0;
	group->y = 0;
	group->big = false;
	group->pattern = 0;
	group->rotation = 0;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			group->puyo[y][x] = PuyoColor::Empty;
		}
	}

	group->num = rand() % 3 + 2;

	switch (group->num)
	{
		//�Ղ悪2�̂Ƃ�
		/*
		������	 ������
		������	 ������
		������	 ������
		*/
	case 2:
		group->puyo[0][1] = (PuyoColor)(rand() % 5);
		group->puyo[1][1] = (PuyoColor)(rand() % 5);
		group->pattern = (group->puyo[0][1] == group->puyo[1][1]) ? 1 : 0;
		break;

		//�Ղ悪3�̎�
		/*
		������
		������
		������
		*/
	case 3:
		group->puyo[0][1] = (PuyoColor)(rand() % 5);
		group->puyo[1][1] = group->puyo[0][1];
		group->puyo[1][2] = (PuyoColor)(rand() % 5);
		group->pattern = (group->puyo[1][1] == group->puyo[1][2]) ? 3 : 2;
		break;

		//�Ղ悪4�̎�
		/*
		������
		������
		������
		*/
	case 4:
		group->big = (rand() % 2) ? true : false;
		if (group->big)
		{
			group->puyo[0][1] = (PuyoColor)(rand() % 5);
			group->puyo[0][2] = group->puyo[0][1];
			group->puyo[1][1] = group->puyo[0][1];
			group->puyo[1][2] = group->puyo[0][1];
		}
		else
		{
			int colors[5] = {0,1,2,3,4};
			for (int i = 0; i < 10; i++)
			{
				int a= rand() % 5;
				int b= rand() % 5;
				int c;
				c = colors[a];
				colors[a] = colors[b];
				colors[b] = c;
			}

			group->puyo[0][1] = (PuyoColor)colors[1];
			group->puyo[0][2] = (PuyoColor)colors[2];
			group->puyo[1][1] = group->puyo[0][1];
			group->puyo[1][2] = group->puyo[0][2];
			group->pattern = 4;
		}
		break;
	}
}

//���삵�Ă���Ղ�̕`��Ɋւ���ւ���
void PlayScene::RenderPuyoGroup(const PuyoGroup * group)
{
	//�ł��Ղ�̎�
	if (group->big)
	{
		DrawSprite(
			FIELD_OFFSET_X + group->x + PUYO_SIZE * 1,
			FIELD_OFFSET_Y + group->y,
			PUYO_SIZE *2,
			PUYO_SIZE *2,
			puyogroup,
			(float)PUYO_IMAGE_WIDTH* (int)group->puyo[0][1],
			272,
			PUYO_SIZE *2,
			PUYO_SIZE *2,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			0
		);
	}
	else
	{
		//	������
		//	������	
		//	������	
		if (group->pattern == 0)
		{
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if (group->puyo[y][x] != PuyoColor::Empty)
					{
						DrawSpriteEx(
							FIELD_OFFSET_X + group->x + x * PUYO_SIZE,
							FIELD_OFFSET_Y + group->y + y * PUYO_SIZE,
							PUYO_SIZE,
							PUYO_SIZE,
							0.5f,
							0.5f,
							D3DXToRadian(group->rotation * 90),
							puyogroup,
							(float)PUYO_IMAGE_WIDTH * (int)group->puyo[y][x],
							0,
							PUYO_SIZE,
							PUYO_SIZE,
							D3DCOLOR_ARGB(255, 255, 255, 255),
							0
						);
					}
				}
			}
		}
		//������
		//������
		//������
		else if (group->pattern == 1)
		{
			DrawSpriteEx(
				FIELD_OFFSET_X + group->x + PUYO_SIZE * 1,
				FIELD_OFFSET_Y + group->y,
				PUYO_SIZE,
				PUYO_SIZE * 2,
				0.5f,
				0.75f,
				D3DXToRadian(group->rotation * 90),
				puyogroup,
				(float)PUYO_IMAGE_WIDTH * (int)group->puyo[1][1],
				66,
				PUYO_SIZE,
				PUYO_SIZE * 2,
				D3DCOLOR_ARGB(255, 255, 255, 255),
				0
			);
		}
		//������
		//������
		//������
		else if (group->pattern == 2)
		{
			DrawSpriteEx(
				FIELD_OFFSET_X + group->x + PUYO_SIZE * 1,
				FIELD_OFFSET_Y + group->y ,
				PUYO_SIZE,
				PUYO_SIZE*2,
				0.5f,
				0.75f,
				D3DXToRadian(group->rotation * 90),
				puyogroup,
				(float)PUYO_IMAGE_WIDTH * (int)group->puyo[1][1],
				66,
				PUYO_SIZE,
				PUYO_SIZE * 2,
				D3DCOLOR_ARGB(255, 255, 255, 255),
				0
			);

			static const int table[4][2] = { {2,1},{1,2},{0,1},{1,0} };
			const int x = table[group->rotation][0];
			const int y = table[group->rotation][1];

			DrawSpriteEx(
				FIELD_OFFSET_X + group->x + PUYO_SIZE * x,
				FIELD_OFFSET_Y + group->y + PUYO_SIZE * y,
				PUYO_SIZE,
				PUYO_SIZE,
				0.5f,
				0.5f,
				D3DXToRadian(group->rotation * 90),
				puyogroup,
				(float)PUYO_IMAGE_WIDTH * (int)group->puyo[y][x],
				0,
				PUYO_SIZE,
				PUYO_SIZE,
				D3DCOLOR_ARGB(255, 255, 255, 255),
				0
			);
		}
		//������
		//������
		//������
		else if (group->pattern == 3)
		{
			DrawSpriteEx(
				FIELD_OFFSET_X + group->x + PUYO_SIZE * 1,
				FIELD_OFFSET_Y + group->y,
				PUYO_SIZE * 2,
				PUYO_SIZE * 2,
				0.25f,
				0.75f,
				D3DXToRadian(group->rotation * 90),
				puyogroup,
				(float)PUYO_IMAGE_WIDTH * (int)group->puyo[1][1],
				170,
				PUYO_SIZE * 2,
				PUYO_SIZE * 2,
				D3DCOLOR_ARGB(255, 255, 255, 255),
				0
			);
		}
		//������
		//������
		//������
		else if (group->pattern == 4)
		{
			// ���c�Q��
			{
				static const int table[4][2] = { {1,1},{1,0},{2,0},{2,1} };
				const int x = table[group->rotation][0];
				const int y = table[group->rotation][1];
				DrawSpriteEx(
					FIELD_OFFSET_X + group->x + PUYO_SIZE * 1,
					FIELD_OFFSET_Y + group->y,
					PUYO_SIZE,
					PUYO_SIZE * 2,
					1.0f,
					0.5f,
					D3DXToRadian(group->rotation * 90),
					puyogroup,
					(float)PUYO_IMAGE_WIDTH * (int)group->puyo[y][x],
					66,
					PUYO_SIZE,
					PUYO_SIZE * 2,
					D3DCOLOR_ARGB(255, 255, 255, 255),
					0
				);
			}
			//�E�c2��
			{
				static const int table[4][2] = { {2,1},{1,1},{1,0},{2,0} };
				const int x = table[group->rotation][0];
				const int y = table[group->rotation][1];

				DrawSpriteEx(
					FIELD_OFFSET_X + group->x + PUYO_SIZE * 2,
					FIELD_OFFSET_Y + group->y,
					PUYO_SIZE,
					PUYO_SIZE * 2,
					0.0f,
					0.5f,
					D3DXToRadian(group->rotation * 90),
					puyogroup,
					(float)PUYO_IMAGE_WIDTH * (int)group->puyo[y][x],
					66,
					PUYO_SIZE,
					PUYO_SIZE * 2,
					D3DCOLOR_ARGB(255, 255, 255, 255),
					0
				);
			}
		}
	}
}

PlayScene::PlayScene(const char * name)
	:Scene(name)
{
}

void PlayScene::OnCreate()
{
	//�e�N�X�`���̓ǂݍ���
	background1 = LoadTexture("Assets/Textures/pkayback.png");
	background2 = LoadTexture("Assets/Textures/title.png");
	background3 = LoadTexture("Assets/Textures/01m2.png");
	backgroundfield = LoadTexture("Assets/Textures/01s.png");
	puyopuyo = LoadTexture("Assets/Textures/puyo.png");
	puyogroup = LoadTexture("Assets/Textures/puyogroup.png");
	nextcercle = LoadTexture("Assets/Textures/images.png");
	nextcercle2 = LoadTexture("Assets/Textures/nextcercle2.png");
	next = LoadTexture("Assets/Textures/next.png");
	win = LoadTexture("Assets/Textures/win.png");
	bar = LoadTexture("Assets/Textures/greenbar.png");
	score = LoadTexture("Assets/Textures/score.png");
	highscore = LoadTexture("Assets/Textures/highscore.png");
	combo = LoadTexture("Assets/Textures/combo.png");
	maxcombo = LoadTexture("Assets/Textures/maxcombo.png");
	scorenumber = LoadTexture("Assets/Textures/cm_04.png");
	rule = LoadTexture("Assets/Textures/rule.png");
	gameover = LoadTexture("Assets/Textures/gameover.png");
	//�T�E���h�̓ǂݍ���
	m_playBGM1 = OpenSound("Assets/Audio/BGM2/play.wav");
	m_playBGM2 = OpenSound("Assets/Audio/BGM2/play2.wav");
	m_playBGM3 = OpenSound("Assets/Audio/BGM2/play3.wav");
	m_bombSE = OpenSound("Assets/Audio/SE2/bomb.wav");
	m_rotateSE = OpenSound("Assets/Audio/SE2/rotate.wav");
	m_dropSE = OpenSound("Assets/Audio/SE2/drop.wav");
	m_moveSE = OpenSound("Assets/Audio/SE2/move.wav");
	//������
	m_highscore = 0;
}

void PlayScene::OnStart()
{
	//������
	m_playState = PlayState::Controllable;
	m_effectManager = new EffectManager();
	if (GlobalData::GetInstance()->GetBGM() == BGM::BGM2)
		PlaySound2(m_playBGM2, -1, false);
	else if (GlobalData::GetInstance()->GetBGM() == BGM::BGM3)
		PlaySound2(m_playBGM3, -1, false);
	else
		PlaySound2(m_playBGM1, -1, false);
	m_comboCount = 0;
	m_maxcomboCount=0;
	m_score = 0;

	//�t�B�[���h�̏�����
	for (int y = 0; y < FIELD_NUM_Y; y++)
	{
		for (int x = 0; x < FIELD_NUM_X; x++)
		{
			m_field[y][x] = PuyoColor::Empty;

		}
	}
	GeneratePuyoGroup(&m_secondGroup);
	m_secondGroup.x = SECOND_POS_X;
	m_secondGroup.y = SECOND_POS_Y;
	GeneratePuyoGroup(&m_nextGroup);
	m_nextGroup.x = NEXT_POS_X;
	m_nextGroup.y = NEXT_POS_Y;
	GeneratePuyoGroup(&m_currGroup);
	m_currGroup.x = PUYO_SIZE * 1;
	m_currGroup.y = PUYO_SIZE * 0;

	m_deletablePuyoCount = 0;
	m_floatingCount = 0;

	m_pressRightBefore = false;
	m_pressLeftBefore = false;
	m_pressUpBefore = false;
	m_pressDownBefore = false;
	m_pressABefore = false;
	m_pressDBefore = false;
	m_pressSpaceBefore = false;
}

//������I�����Ղ�Ɋւ���֐�
void PlayScene::FixGroupOnField(const PuyoGroup*group)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (group->puyo[y][x] != PuyoColor::Empty)
			{
				const int fx = (int)(group->x / PUYO_SIZE) + x;
				const int fy = (int)(group->y / PUYO_SIZE) + y;
				m_field[fy][fx] = group->puyo[y][x];

			}
		}
	}
}

//�����Ă���Ղ悪�u����ꏊ��T������֐�
bool PlayScene::Putableone(const FloatingPuyo*puyo)
{
	for (int y = 0; y < FIELD_NUM_Y; y++)
	{
		for (int x = 0; x < FIELD_NUM_X; x++)
		{
			int left = (int)puyo->x + (PUYO_SIZE * x);
			int right = left + PUYO_SIZE;
			int top = (int)puyo->y + (PUYO_SIZE * y);
			int bottom = top + PUYO_SIZE;
			//����R�p�^�[���@
			if (left < 0 || right>PUYO_SIZE*FIELD_NUM_X || top < 0 || bottom>PUYO_SIZE*FIELD_NUM_Y)
			{
				return false;
			}
			//�t�B�[���h��̂Ղ�̔���
			const int fx = (int)(puyo->x / PUYO_SIZE) + x;
			const int fy = (int)(puyo->y / PUYO_SIZE) + y;
			if (m_field[fy + 1][fx] != PuyoColor::Empty)
			{
				return false;
			}
		}
	}
	return true;
}

//���삵�Ă���Ղ���E��]������֐�
void PlayScene::RotateRight(PuyoGroup * group)
{
	//�ł��Ղ�̂Ƃ�
	if (group->big)
	{
		PuyoColor color = group->puyo[1][1];
		color = (PuyoColor)(((int)color + 1) % 5);
		group->puyo[0][1] = color;
		group->puyo[0][2] = color;
		group->puyo[1][1] = color;
		group->puyo[1][2] = color;

	}
	//4�̎�
	else if (group->num==4)
	{
		PuyoGroup copypuyo = *group;
		group->puyo[0][1] = copypuyo.puyo[1][1];
		group->puyo[0][2] = copypuyo.puyo[0][1];
		group->puyo[1][2] = copypuyo.puyo[0][2];
		group->puyo[1][1] = copypuyo.puyo[1][2];
		group->rotation = (group->rotation >= 3) ?  0:group->rotation + 1 ;

	}
	else
	{
		PuyoGroup copypuyo = *group;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				group->puyo[x][2 - y] = copypuyo.puyo[y][x];
			}
		}

		if (!Putable(group)){
			*group=copypuyo;
		}else {
			group->rotation = (group->rotation >= 3) ? 0 : group->rotation + 1;
		}
	}
}

//���삵�Ă���Ղ������]������֐�
void PlayScene::RotateLeft(PuyoGroup * group)
{	
	//�ł��Ղ�̂Ƃ�
	if (group->big)
	{
		PuyoColor color = group->puyo[1][1];
		color = (PuyoColor)(((int)color + 1) % 5);
		group->puyo[0][1] = color;
		group->puyo[0][2] = color;
		group->puyo[1][1] = color;
		group->puyo[1][2] = color;
	}
	//4�̎�
	else if (group->num == 4)
	{
		PuyoGroup copypuyo = *group;
		group->puyo[1][1] = copypuyo.puyo[0][1];
		group->puyo[1][2] = copypuyo.puyo[1][1];
		group->puyo[0][2] = copypuyo.puyo[1][2];
		group->puyo[0][1] = copypuyo.puyo[0][2];
		group->rotation = (group->rotation >= 1) ? group->rotation - 1 : 3;
	}
	else
	{
		PuyoGroup copypuyo = *group;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				group->puyo[2-x][y] = copypuyo.puyo[y][x];
			}
		}

		if (!Putable(group)) {
			*group = copypuyo;
		} else {
			group->rotation = (group->rotation >= 1) ? group->rotation - 1 : 3;
		}
	}
}

//�Ղ悪�u�����Ƃ��\�����ʂ���֐�
bool PlayScene::Putable(const PuyoGroup*group)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			//�g���ɂՂ悪���݂��邩����
			if (group->puyo[y][x] != PuyoColor::Empty)
			{
				int left = (int)group->x + (PUYO_SIZE * x);
				int right = left + PUYO_SIZE;
				int top = (int)group->y + (PUYO_SIZE * y);
				int bottom = top + PUYO_SIZE;
				//����R�p�^�[���@
				if (left < 0 || right>PUYO_SIZE*FIELD_NUM_X || top < 0 || bottom>PUYO_SIZE*FIELD_NUM_Y)
				{
					return false;
				}
				//�t�B�[���h��̂Ղ�̔���
				const int fx = (int)(group->x / PUYO_SIZE) + x;
				const int fy = (int)(group->y / PUYO_SIZE) + y;
				if (m_field[fy+1][fx]!= PuyoColor::Empty)
				{
					return false;
				}
			}
		}
	}
	return true;
}

//�����Ă���Ղ��T���֐�
bool PlayScene::FindFloatingPuyo()
{
	m_floatingCount = 0;

	//�t�B�[���h�̈�ԉ��̈�i�ォ��T��
	for (int x = 0; x < FIELD_NUM_X; x++)
	{
		bool isFloating = false;

		for (int y = FIELD_NUM_Y-1; y >= 0; y--)
		{
			if (isFloating)
			{
				if (m_field[y][x] != PuyoColor::Empty)
				{
					m_floatigs[m_floatingCount].color = m_field[y][x];
					m_floatigs[m_floatingCount].x = (float)PUYO_SIZE * x;
					m_floatigs[m_floatingCount].y = (float)PUYO_SIZE * y;
					m_floatigs[m_floatingCount].vx = 0;
					m_floatigs[m_floatingCount].vy = 0;
					m_floatingCount++;

					/*(��)'��'���������u��'��'������
					����������          ���������@�@�@�@�������~
					����������    ��    ���������@�@���@��������
					����������          ���������@�@�@�@��������
					*/
					//�t�B�[���h�ォ�����(�~�̂Ƃ���)
					m_field[y][x] = PuyoColor::Empty;

				}
			}
			else
			{
				if (m_field[y][x] == PuyoColor::Empty)
					isFloating = true;
			}
		}
	}
	return m_floatingCount > 0;
}

//��~����ɕ����Ă���Ղ�𗎉�������֐�
// �߂�l�F���ׂė��Ƃ��I�������true��Ԃ�
bool PlayScene::DropFloatingPuyo()
{
	bool allDropped=true;
	for (int i = 0; i < m_floatingCount; i++)
	{
		if (m_floatigs[i].color != PuyoColor::Empty)
		{
			// �V�����ʒu = ���݂̈ʒu + ���݂̑��x
			m_floatigs[i].x = m_floatigs[i].x + m_floatigs[i].vx;
			m_floatigs[i].y = m_floatigs[i].y + m_floatigs[i].vy;


			// �V�������x = ���݂̑��x + ���݂̉����x
			m_floatigs[i].vx = m_floatigs[i].vx + FLOATING_PUYO_AX;
			m_floatigs[i].vy = m_floatigs[i].vy + FLOATING_PUYO_AY;


			//�t�B�[���h��̂Ղ�̔���
			const int fx = (int)(m_floatigs[i].x / PUYO_SIZE);
			const int fy = (int)(m_floatigs[i].y / PUYO_SIZE);
			if (m_field[fy + 1][fx] != PuyoColor::Empty)
			{
				m_field[fy][fx] = m_floatigs[i].color;
				m_floatigs[i].color = PuyoColor::Empty;
				continue;
			}
			allDropped = false;
		}
	}
	return allDropped;
}

//�������Ղ�̗�����̕`��Ɋւ���֐�
void PlayScene::RenderFloatingPuyo()
{
	for (int i = 0; i < m_floatingCount; i++)
	{
		if (m_floatigs[i].color != PuyoColor::Empty)
		{
			DrawSprite((float)FIELD_OFFSET_X + m_floatigs[i].x, (float)FIELD_OFFSET_Y + m_floatigs[i].y, 40, 40,
				puyogroup, (float)PUYO_IMAGE_WIDTH * (int)m_floatigs[i].color, 0, 40, 40, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
		}
	}
}

//�����F�̂Ղ悪�Ȃ����Ă��邩�ǂ������ׂ�֐�
void PlayScene::FindLinkedPuyo(PuyoColor color, int x, int y, std::vector<Position> & linked)
{
	// ���łɒT���ς݂Ȃ��
	if (m_found[y][x])
		return;

	// �Ղ悪���Ȃ�
	if (color == PuyoColor::Empty)
		return;

	// �����F�̂Ղ悩�H
	if (m_field[y][x] != color)
		return;

	// ��U���̏ꏊ(x, y)��ۑ����Ă���
	linked.push_back({ x, y });

	// �T���ς݃t���O��true�ɂ���
	m_found[y][x] = true;

	// ��𒲂ׂɍs��
	if (y - 1 >= 0)
		FindLinkedPuyo(color, x + 0, y - 1, linked); 
	
	// �E�𒲂ׂɍs��
	if (x + 1 < FIELD_NUM_X)
		FindLinkedPuyo(color, x + 1, y + 0, linked); 
	
	// ���𒲂ׂɍs��
	if (y + 1 < FIELD_NUM_Y)
		FindLinkedPuyo(color, x + 0, y + 1, linked);

	// ���𒲂ׂɍs��
	if (x - 1 >= 0)
		FindLinkedPuyo(color, x - 1, y + 0, linked); 
}

//�Ղ����������
void PlayScene::DeletePuyos()
{
	for (int i = 0; i < m_deletablePuyoCount; i++)
	{
		int x = m_deletablePuyos[i].x;
		int y = m_deletablePuyos[i].y;

		//�G�t�F�N�g����
		DeleteEffect*deleteEffect=new DeleteEffect();
		deleteEffect->SetPosition((float)FIELD_OFFSET_X+PUYO_SIZE*x-8, (float)FIELD_OFFSET_Y+PUYO_SIZE*y);
		m_effectManager->AddEffect(deleteEffect);

		m_field[y][x] = PuyoColor::Empty;
	}
	m_deletablePuyoCount = 0;
	m_comboCount += 1;
	//�X�R�A����
	for (int i = 0; i < m_comboCount; i++)
	{
		if (i < 10)
		{
			m_score += 300;
		}
		else
		{
			m_score += 500;
		}
	}
	//�A������
	if (m_maxcomboCount < m_comboCount)
	{
		m_maxcomboCount = m_comboCount;
	}
	//�G�t�F�N�g����
	ComboEffect*combo = new ComboEffect(1.0f, m_comboCount);
	combo->SetPosition(330, 330);
	m_effectManager->AddEffect(combo);
}

//������Ղ��T������֐�
bool PlayScene::FindDeletablePuyo()
{
	std::vector<Position> linked;

	// �T���ς݃t���O��false�ɂ���
	memset(m_found, 0, sizeof(m_found));

	m_deletablePuyoCount = 0;

	for (int y = 0; y < FIELD_NUM_Y; y++)
	{
		for (int x = 0; x < FIELD_NUM_X; x++)
		{
			if (m_field[y][x] != PuyoColor::Empty)
			{
				if (m_found[y][x] == false)
				{
					linked.clear();
					FindLinkedPuyo(m_field[y][x], x, y, linked);

					if (linked.size() >= 4)
					{
						// 4�ȏ�q�����Ă���Ղ���������I
						for (unsigned int i = 0; i < linked.size(); i++)
						{
							m_deletablePuyos[m_deletablePuyoCount++] = linked[i];
							if (linked.size() >= 5)
							{
								m_score += 100;
							}
						}
					}
				}
			}
		}
	}
	return (m_deletablePuyoCount > 0);
}

//�Q�[���I�[�o�[���C����̂Ղ��������֐�
bool PlayScene::FindGameOverLine()
{
	bool notDelete = false;
	for (int x = 0; x < FIELD_NUM_X; x++)
	{
		if (m_field[1][x] != PuyoColor::Empty)
		{
			notDelete = true;
		}
	}
	return notDelete;
}

//�X�R�A��`�悷��֐�
void PlayScene::RenderScore(int x, int y, int score)
{
	//�����Ƃɕ�����
	int digit[10];
	//�������L��������
	int count = 0;

	while (score > 0)
	{
		digit[count] = score % 10;
		score /= 10;
		count++;
	}
	for (int i = 0; i < count; i++)
	{
		char value = digit[count - i - 1];

		DrawSprite(i * 24.0f + x, (float)y, 24, 48, scorenumber, 24.0f*value,0,24,48, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

//�A����`�悷��֐�
void PlayScene::RenderMaxCombo(int x, int y, int combo)
{
	//�����Ƃɕ�����
	char digit[4];
	//�������L��������
	char digitCounts = 0;
	while (combo > 0)
	{
		digit[digitCounts] = combo % 10;
		combo /= 10;
		digitCounts++;
	}
		
	for (int i = 0; i < digitCounts; i++)
	{		
		char value = digit[digitCounts -i - 1];
		//�R���{��
		DrawSprite(x + 24.0f * i, (float)y, 24, 48, scorenumber, 24.0f * value, 0, 24, 48);
	}
	
	//�u��񂳁I�v
	DrawSprite(x + 24.0f * digitCounts, y + 15.0f, 128.0f, 32.0f, scorenumber, 0.0f, 50.0f, 128.0f, 32.0f);

}

void PlayScene::OnUpdate(float deltaTime)
{
	m_pressRight = (GetKeyState(VK_RIGHT) & 0x8000) ? true : false;
	m_pressLeft = (GetKeyState(VK_LEFT) & 0x8000) ? true : false;
	m_pressUp = (GetKeyState(VK_UP) & 0x8000) ? true : false;
	m_pressDown = (GetKeyState(VK_DOWN) & 0x8000) ? true : false;
	m_pressA = (GetKeyState('A') & 0x8000) ? true : false;
	m_pressD = (GetKeyState('D') & 0x8000) ? true : false;
	m_pressSpace = (GetKeyState(VK_SPACE) & 0x8000) ? true : false;
/*
	//�G�t�F�N�g�m�F�p
	if (!m_pressSpace&&m_pressSpaceBefore)
	{
	}
*/
	switch (m_playState)
	{
	//����\
	case PlayState::Controllable:
		m_comboCount = 0;
		//�u���v�L�[
		if (m_pressDown)
		{
			m_currGroup.y += 8;
		}
		else
		{
			m_currGroup.y += 1;
		}
		//�uD�v�L�[:��]
		if (!m_pressDBefore &&m_pressD)
		{
			RotateRight(&m_currGroup);
			PlaySound2(m_rotateSE, 1, false);
		}
		//�uA�v�L�[:��]
		if (!m_pressABefore &&m_pressA)
		{
			RotateLeft(&m_currGroup);
			PlaySound2(m_rotateSE, 1, false);
		}

		if (!Putable(&m_currGroup))
		{
			FixGroupOnField(&m_currGroup);
			PlaySound2(m_dropSE, 1, false);
			m_score += 100;
			if (FindFloatingPuyo())
			{
				m_playState = PlayState::DropFloatings;
			}
			else if (FindDeletablePuyo())
			{
				m_playState = PlayState::DeleteAnimation;
			}
			else if (FindGameOverLine())
			{
				m_playState = PlayState::GameOver;
			}

			m_currGroup = m_nextGroup;
			m_currGroup.x = PUYO_SIZE * 1;
			m_currGroup.y = PUYO_SIZE * 0;
			m_nextGroup = m_secondGroup;		
			m_nextGroup.x = NEXT_POS_X;
			m_nextGroup.y = NEXT_POS_Y;
			GeneratePuyoGroup(&m_secondGroup);
			m_secondGroup.x = SECOND_POS_X;
			m_secondGroup.y = SECOND_POS_Y;
		}
		//�u���v�L�[:�ړ�
		if (!m_pressRightBefore &&m_pressRight)
		{
			m_currGroup.x += PUYO_SIZE;

			if (!Putable(&m_currGroup))
			{
				m_currGroup.x -= PUYO_SIZE;
			}
			PlaySound2(m_moveSE, 1, false);
		}
		//�u���v�L�[:�ړ�
		else if (!m_pressLeftBefore &&m_pressLeft)
		{
			m_currGroup.x -= PUYO_SIZE;
			if (!Putable(&m_currGroup))
			{
				m_currGroup.x += PUYO_SIZE;

			}
			PlaySound2(m_moveSE, 1, false);
		}

		break;
	//��������
	case PlayState::DeleteAnimation:
		
		DeletePuyos();
		PlaySound2(m_bombSE, 1, false);

		if (FindFloatingPuyo())
		{
			m_playState = PlayState::DropFloatings;
		}
		else if (FindGameOverLine())
		{
			m_playState = PlayState::GameOver;
		}
		else
		{
			m_playState = PlayState::Controllable;
		}
		break;

	//�����Ă�Ղ�̏���
	case PlayState::DropFloatings:

		if (DropFloatingPuyo())
		{
			PlaySound2(m_dropSE, 1, false);

			if (FindDeletablePuyo())
			{
				m_playState = PlayState::DeleteAnimation;
			}
			else
			{
				m_playState = PlayState::Controllable;
			}
		}
		break;
	//�Q�[���I�[�o�[
	case PlayState::GameOver:
		if(m_highscore<m_score)
			m_highscore = m_score;
		StopSound(m_playBGM1);
		StopSound(m_playBGM2);
		StopSound(m_playBGM3);

		if (!m_pressSpace&&m_pressSpaceBefore)
		{
			SceneManager::GetInstance()->ReserveNextScene("�^�C�g��");
		}
		break;
	}

	m_pressRightBefore = m_pressRight;
	m_pressLeftBefore = m_pressLeft;
	m_pressUpBefore = m_pressUp;
	m_pressDownBefore = m_pressDown;
	m_pressSpaceBefore = m_pressSpace;
	m_pressABefore = m_pressA;
	m_pressDBefore = m_pressD;

	m_effectManager->UpdateAllEffects();
}

void PlayScene::OnRender()
{
	//�w�i
	if (GlobalData::GetInstance()->GetBackGround() == BackGround::BackGround2)
		DrawSprite(0, 0, 800, 600, background2, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else if (GlobalData::GetInstance()->GetBackGround() == BackGround::BackGround3)
		DrawSprite(0, 0, 800, 600, background3, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	else
		DrawSprite(0, 0, 800, 600, background1, 0, 0, 800, 600, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	FillRect(310, 50, 440, 570-50, D3DCOLOR_ARGB(200, 112, 128, 144));
	//����@
	FillRect(500, 60, 240, 160, D3DCOLOR_ARGB(200, 200, 200, 200));
	DrawSprite(500,60, 337,150, rule, 0, 0, 337, 150, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	//�l�N�X�g�Ղ�
	DrawSprite(310, 50, 104, 54, next, 0, 0, 104, 54, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	//DrawSprite(400, 60, 90, 46, next, 0, 0, 90, 46, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	
	//�A����
	DrawSprite(320, 250, 157, 55, combo, 0, 0, 157, 55, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	DrawSprite(500, 250, 234, 55, maxcombo, 0, 0, 234, 55, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	//�X�R�A
	DrawSprite(340, 420, 134, 55, score, 0, 0, 134, 55, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	DrawSprite(500, 420, 219, 56, highscore, 0, 0, 219, 56, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	// ��������1P��
	D3DVIEWPORT9 viewportSaved;
	GetD3DDevice()->GetViewport(&viewportSaved);

	D3DVIEWPORT9 viewport1P;
	viewport1P.X = FIELD_OFFSET_X;
	viewport1P.Y = FIELD_OFFSET_Y + PUYO_SIZE * 2;
	viewport1P.Width = PUYO_SIZE * FIELD_NUM_X;
	viewport1P.Height = PUYO_SIZE * FIELD_NUM_Y;
	viewport1P.MinZ = 0.0f;
	viewport1P.MaxZ = 1.0f;
	GetD3DDevice()->SetViewport(&viewport1P);

	//�g���w�i
	//������
	DrawSprite(FIELD_OFFSET_X, FIELD_OFFSET_Y + PUYO_SIZE * 2, 240, 480, backgroundfield, 0, 0, 640,480, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	// �t�B�[���h��ɌŒ肳�ꂽ�Ղ�B
	for (int y = 0; y < FIELD_NUM_Y; y++)
	{
		for (int x = 0; x < FIELD_NUM_X; x++)
		{
			if (m_field[y][x] != PuyoColor::Empty)
			{
				DrawSprite((float)FIELD_OFFSET_X +x  * PUYO_SIZE, (float)FIELD_OFFSET_Y +  y * PUYO_SIZE, 40, 40, puyogroup, (float)PUYO_IMAGE_WIDTH * (int)m_field[y][x], 0, 40, 40, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
			}
		}
	}

/*	�m�F�p
//�c��
	for (float x = 0; x < 7; x++)
	{
		FillRect(FIELD_OFFSET_X + PUYO_SIZE * x, FIELD_OFFSET_Y, 2, PUYO_SIZE * FIELD_NUM_Y, D3DCOLOR_ARGB(255, 245, 245, 245));
	}

	//����
	for (float y = 0; y < 15; y++)
	{
		FillRect(FIELD_OFFSET_X, FIELD_OFFSET_Y + (PUYO_SIZE * y), PUYO_SIZE * FIELD_NUM_X, 2, D3DCOLOR_ARGB(255, 245, 245, 245));
	}
	*/
	RenderPuyoGroup(&m_currGroup);
	RenderFloatingPuyo();

	//��]�K�C�h�i�O���[�j
	//�c��
	for (float x = 0; x < 4; x++)
	{
		FillRect(FIELD_OFFSET_X + m_currGroup.x + PUYO_SIZE * x, FIELD_OFFSET_Y +m_currGroup.y, 2, PUYO_SIZE * 3,
			D3DCOLOR_ARGB(255, 119, 136, 153));
	}
	//����
	for (float y = 0; y < 4; y++)
	{
		FillRect(FIELD_OFFSET_X + m_currGroup.x, FIELD_OFFSET_Y + m_currGroup.y + (PUYO_SIZE * y), PUYO_SIZE * 3, 2,
			D3DCOLOR_ARGB(255, 119, 136, 153));
	}

	// 1P���`�悱���܂�
	GetD3DDevice()->SetViewport(&viewportSaved);

	DrawSprite(70, 50, 310 - 70, 40, bar, 0, 0, 180, 30, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	RenderPuyoGroup(&m_nextGroup);
	RenderPuyoGroup(&m_secondGroup);
	if (m_playState == PlayState::GameOver)
		DrawSprite(70, 180, 241, 195, gameover, 0, 0, 241, 195, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

	RenderScore(320, 480,m_score);
	RenderScore(520, 480, m_highscore);

	if(m_maxcomboCount>0)
		RenderMaxCombo(550, 330,m_maxcomboCount);
	
	m_effectManager->RenderAllEffects();
}

void PlayScene::OnStop()
{
}

void PlayScene::OnDestroy()
{
}

