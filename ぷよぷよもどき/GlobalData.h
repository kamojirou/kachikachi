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

	//�g���w�i���Z�b�g
	void SetBackGround(BackGround selectBackGround);
	//�g��BGM���Z�b�g
	void SetBGM(BGM selectBGM);
	//�g���w�i���擾
	BackGround GetBackGround()const;
	//�g��BGM���擾
	BGM GetBGM()const;

};