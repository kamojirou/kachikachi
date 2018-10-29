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
	Obstacle,//お邪魔ぷよ
	Empty
};

struct PuyoGroup
{
	//ぷよの情報
	/*
	□□□
	□□□
	□□□
	*/

	/*
	[0][0]	[0][1]	[0][2]			[2][0]	[1][0]	[0][0]
	[1][0]	[1][1]	[1][2]			[2][1]	[1][1]	[0][1]
	[2][0]	[2][1]	[2][2]			[2][2]	[1][2]	[0][2]

									[+2][+0] [+1][-1] [+0][-2]
									[-1][-1] [+0][+0] [-1][-1]
									[-0][+2] [-1][+1] [-2][+0]
	右回転							左回転
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

	//4個分のぷよ(でかぷよ)かどうか判別
	bool big;

	//フィールド左隅からのピクセル単位の位置
	float x;
	float y;

	//ぷよの個数
	int num;

	// 配置パターン
	//    0            1           2           3           4           5
	//	□○□		□○□	 	 □○□ 	 □○□ 	 □○△ 	 □○○
	//	□△□		□○□	 	 □○△ 	 □○○ 	 □○△ 	 □○○
	//	□□□		□□□	 	 □□□ 	 □□□ 	 □□□ 	 □□□
	int pattern;

	//右に何回転しているか
	int rotation;
};

// 浮いているぷよ一個分
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
	//プレイヤーが操作可能な状態
	Controllable,
	//ぷよがつながって消えている状態
	DeleteAnimation,
	//浮いているぷよが落下している状態
	DropFloatings,
	//ぷよがゲームオーバーラインで消えなかった状態
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
	//テクスチャに関する変数
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
	//サウンドに関する変数
	unsigned short m_playBGM1;
	unsigned short m_playBGM2;
	unsigned short m_playBGM3;
	unsigned short m_rotateSE;
	unsigned short m_moveSE;
	unsigned short m_dropSE;
	unsigned short m_bombSE;

	//ぷよに関する変数
	PuyoGroup m_currGroup;
	PuyoGroup m_nextGroup;
	PuyoGroup m_secondGroup;

	//操作処理に関する変数
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

	//左回転
	bool m_pressABefore;
	bool m_pressA;
	//右回転
	bool m_pressDBefore;
	bool m_pressD;

	//フィールドの差分（ピクセル単位）
	static const int FIELD_OFFSET_X = 70;
	static const int FIELD_OFFSET_Y = 10;

	//フィールドのマス目
	static const int FIELD_NUM_X = 6;
	static const int FIELD_NUM_Y = 14;
	//ネクストぷよの位置
	static const int NEXT_POS_X = 205;
	static const int NEXT_POS_Y = 90;
	//セカンドぷよの位置
	static const int SECOND_POS_X = 300;
	static const int SECOND_POS_Y = 160;

	//ぷよ画像の色の間隔幅
	static const int PUYO_IMAGE_WIDTH = 94;

	//ぷよ一個分の大きさ 幅40　高さ40
	static const int PUYO_SIZE =40;

	//浮いているぷよの加速度(落下時)
	static const float FLOATING_PUYO_AX;
	static const float FLOATING_PUYO_AY;

	//フィールドの配列
	PuyoColor m_field[FIELD_NUM_Y][FIELD_NUM_X];
	// 探索済みフラグ
	bool m_found[FIELD_NUM_Y][FIELD_NUM_X];

	//消えるぷよ配列
	int m_deletablePuyoCount;
	Position m_deletablePuyos[FIELD_NUM_X*FIELD_NUM_Y];

	//浮いているぷよの個数
	int m_floatingCount;
	FloatingPuyo m_floatigs[FIELD_NUM_X*FIELD_NUM_Y];

	//操作状態
	PlayState m_playState;

	//エフェクト
	EffectManager * m_effectManager;

	//連鎖数
	char m_comboCount;
	char m_maxcomboCount;

	//スコア
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
	//操作しているぷよの描画に関する関する
	void RenderPuyoGroup(const PuyoGroup*group);
	//操作を終えたぷよに関する関数
	void FixGroupOnField(const PuyoGroup*group);
	//ぷよが置ける場所を探索する関数
	bool Putable(const PuyoGroup*group);
	//浮いているぷよを探索する関数
	bool FindFloatingPuyo();
	//浮いているぷよを落下させる関数
	bool DropFloatingPuyo();
	//浮いたぷよの落下後の描画に関する関数
	void RenderFloatingPuyo();
	//void RenderNextPuyoGroup(const PuyoGroup * group);
	//消せるぷよを探索する関数
	bool FindDeletablePuyo();
	//ゲームオーバーライン上のぷよを見つける関数
	bool FindGameOverLine();
	//浮いているぷよが置ける場所を探索する関数
	bool Putableone(const FloatingPuyo*puyo);
	//操作しているぷよを右回転させる関数
	void RotateRight(PuyoGroup*group);
	//操作しているぷよを左回転させる関数
	void RotateLeft(PuyoGroup*group);
	//同じ色のぷよがつながっているかどうか調べる関数
	void FindLinkedPuyo(PuyoColor color, int x,int y, std::vector<Position> & linked);
	//ぷよを消す処理
	void DeletePuyos();
	//スコアを描画する関数
	void RenderScore(int x, int y, int score);
	//連鎖を描画する関数
	void RenderMaxCombo(int x, int y, int combo);
};