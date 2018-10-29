#include "GlobalData.h"
#include <cassert>

GlobalData * GlobalData::s_instance = nullptr;

GlobalData::GlobalData()
{
}


void GlobalData::Startup()
{
	assert(!s_instance);
	s_instance = new GlobalData();
}


void GlobalData::Shutdown()
{
	assert(s_instance);
	delete s_instance;
	s_instance = nullptr;
}


GlobalData * GlobalData::GetInstance()
{
	return s_instance;
}

void GlobalData::SetBackGround(BackGround selectBackGround)
{
	m_selectbackground = selectBackGround;
}

void GlobalData::SetBGM(BGM selectBGM)
{
	m_selectBGM = selectBGM;
}

BackGround GlobalData::GetBackGround()const
{
	return m_selectbackground;
}

BGM GlobalData::GetBGM()const
{
	return m_selectBGM;
}
