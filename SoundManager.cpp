#include "stdafx.h"
#include "SoundManager.h"

const double TIMEDELAY (1000.0f / 60.0f);

void SoundManager::AddSound(string str, LPCWSTR route)
{
	auto iter = m_Sound.find(str);
	if (iter != m_Sound.end()) return;

	mciOpen.lpstrElementName = route;
	mciOpen.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	int dwID = mciOpen.wDeviceID;
	
	m_Sound.insert(make_pair(str, dwID));
}

void SoundManager::Playbgm(string str, bool loop)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;
	
	if (loop == true)
	{
		mciSendCommand(iter->second, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
			(DWORD)(LPVOID)&mciPlay);
	}
	else
	{
		mciSendCommand(iter->second, MCI_PLAY, MCI_NOTIFY,
			(DWORD)(LPVOID)&mciPlay);
	}
	time = 0;
}

void SoundManager::RePlay(string str)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;

	mciSendCommand(iter->second, MCI_RESUME, 0, NULL);
}

void SoundManager::Pause(string str)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;

	mciSendCommand(iter->second, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
}

void SoundManager::Close(string str)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;

	mciSendCommand(iter->second, MCI_CLOSE, 0, NULL);
}

void SoundManager::PlayEffect(LPCWSTR route)
{
	sndPlaySound(L"./droid_destroyed3.wav", SND_ASYNC | SND_NODEFAULT | SND_NOSTOP);
}

void SoundManager::Update()
{
	if (activetime)
	{
		if (lasttime > time)
		{
			time = timeGetTime() + TIMEDELAY * 60.0f;
			second++;
		}
		lasttime = timeGetTime();
	}
}

void SoundManager::Release()
{
	m_Sound.clear();
}

SoundManager::SoundManager()
{
	time = 0;
	second = 0;
	activetime = true;
}


SoundManager::~SoundManager()
{
}
