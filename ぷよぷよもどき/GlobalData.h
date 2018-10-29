#pragma once

enum class BackGround
{
	BackGround1,
	BackGround2,
	BackGround3,
};
enum class BGM
{
	BGM1,
	BGM2,
	BGM3,
};

class GlobalData
{
private:
	static GlobalData * s_instance;
	BackGround m_selectbackground;
	BGM m_selectBGM;

private:
	GlobalData();
	~GlobalData() = default;
	GlobalData(const GlobalData &) = delete;
	GlobalData(GlobalData &&) = delete;
	void operator =(const GlobalData &) = delete;
	void operator =(GlobalData &&) = delete;

public:
	static void Startup();
	static void Shutdown();
	static GlobalData * GetInstance();

	//使う背景をセット
	void SetBackGround(BackGround selectBackGround);
	//使うBGMをセット
	void SetBGM(BGM selectBGM);
	//使う背景を取得
	BackGround GetBackGround()const;
	//使うBGMを取得
	BGM GetBGM()const;

};