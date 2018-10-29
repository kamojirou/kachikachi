#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <unordered_map>
#include <cassert>

#pragma comment(lib,"Winmm.lib")


static HWND hSoundWnd = nullptr;

// 1曲分
struct Sound
{
	unsigned short soundID;
	int loopTimes;
	bool autoClose;
};

// 再生中の曲
std::unordered_map<unsigned short, Sound *> playing;


static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		break;

	case MM_MCINOTIFY:
	{
		if (wParam == MCI_NOTIFY_SUCCESSFUL)
		{
			unsigned short soundID = (unsigned short)lParam;

			auto found = playing.find(soundID);
			if (found == playing.end())
				break;

			Sound * sound = (*found).second;
			
			if (sound->loopTimes < 0)
			{
				PlaySound2(soundID, sound->loopTimes);
			}
			else if (sound->loopTimes > 1)
			{
				PlaySound2(soundID, sound->loopTimes - 1);
			}
			else
			{
				if (sound->autoClose)
				{
					CloseSound(soundID);
				}
				else
				{
					playing.erase(found);
				}
			}
		}
	}
	break;

	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return (0L);
}


void StartupSoundSystem()
{
	assert(!hSoundWnd);

	// ウィンドウクラスの登録
	WNDCLASS wcex;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "サウンドウィンドウクラス";
	if (!RegisterClass(&wcex))
	{
		assert(0);
		return;
	}

	// サウンド用ウィンドウの作成
	hSoundWnd = CreateWindow(wcex.lpszClassName, "サウンドウィンドウ", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, wcex.hInstance, nullptr);
	if (!hSoundWnd)
	{
		MessageBox(nullptr, "サウンドウィンドウの作成に失敗しました", "エラー", MB_OK);
	}
}


void ShutdownSoundSystem()
{
	assert(hSoundWnd);
	DestroyWindow(hSoundWnd);
	hSoundWnd = nullptr;
}


unsigned short OpenSound(const char * path)
{
	MCI_OPEN_PARMS mciOpen;
	memset(&mciOpen, 0, sizeof(mciOpen));
	mciOpen.lpstrDeviceType = (const char *)MCI_DEVTYPE_WAVEFORM_AUDIO;
	mciOpen.lpstrElementName = path;

	if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE_ID | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpen))
	{
		MessageBox(nullptr, "サウンドの再生に失敗しました。", "エラー", MB_OK);
	}

	return mciOpen.wDeviceID;
}

void PlaySound2(unsigned short soundID, int loopTimes, bool autoClose)
{
	assert(hSoundWnd);

	if (loopTimes == 0)
		return;

	auto found = playing.find(soundID);
	if (found == playing.end())
	{
		// 新規登録
		Sound * sound = new Sound();
		sound->soundID = soundID;
		sound->loopTimes = loopTimes;
		sound->autoClose = autoClose;
		playing.insert({ soundID, sound });
	}
	else
	{
		(*found).second->loopTimes = loopTimes;
		(*found).second->autoClose = autoClose;
	}

	MCI_PLAY_PARMS mciPlay;
	mciPlay.dwFrom = 0;		// 再生したい曲の始め
	mciPlay.dwTo = 0;		// 再生したい曲の終わり
	mciPlay.dwCallback = (DWORD_PTR)hSoundWnd;
	mciSendCommand(soundID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD_PTR)&mciPlay);
}


void StopSound(unsigned short soundID)
{
	mciSendCommand(soundID, MCI_STOP, 0, 0);

	auto found = playing.find(soundID);
	if (found != playing.end())
	{
		delete (*found).second;
		playing.erase(found);
	}
}

void CloseSound(unsigned short soundID)
{
	mciSendCommand(soundID, MCI_CLOSE, 0, 0);

	auto found = playing.find(soundID);
	if (found != playing.end())
	{
		delete (*found).second;
		playing.erase(found);
	}
}
