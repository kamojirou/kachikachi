#pragma once
#include <d3d9.h>
#include <vector>

// アニメーション
class Animation
{
public:
	// 1コマ
	struct Frame
	{
		IDirect3DTexture9 * texture;	// どの画像を使う？
		int sx;		// 左上隅X座標
		int sy;		// 左上隅Y座標
		int sw;		// 横幅
		int sh;		// 高さ
		int time;	// 持続時間 (フレーム単位)
	};

private:
	std::vector<Frame> m_frames;

public:
	// コマを追加します。
	void AddFrame(IDirect3DTexture9 * texture, int sx, int sy, int sw, int sh, int time);

	// 総コマ数を取得します。
	int GetFrameCount() const;

	// index番目のコマ情報を取得します。
	const Frame & GetFrameByIndex(int index) const;
};


// アニメーション操作クラス
class AnimationController
{
private:
	Animation * m_animation;	// 再生したいアニメーション
	int m_index;				// 今何コマ目？
	float m_time;				// そのコマを何フレーム表示した？
	
	enum class State
	{
		Playing,	//再生中
		Stopped,	//停止中
		Paused,		//一時停止中
	};

	State m_state;
	int m_looptimes;
	bool m_isFinished;

public:
	// コンストラクタ
	AnimationController();

	// アニメーションを変更します。
	void ChangeAnimation(Animation * animation);

	//アニメーションの再生します。
	// -1:無限ループ	0:再生しない	1:一回再生	2:二回再生	…	
	void Play(int looptimes);

	//アニメーションを停止します。
	void Stop();

	//アニメーションの一時停止します。
	void Pause();

	//アニメーションの一時停止を解除します。
	void Resume();

	//アニメーションが終了している場合、trueを返す
	bool IsFinished()const;

	// アニメーションを更新します。
	void Update(float deltaTime);

	// 現在表示すべきコマを取得します。
	const Animation::Frame & GetCurrentFrame() const;
};
