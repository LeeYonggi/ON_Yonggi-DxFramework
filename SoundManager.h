#pragma once
#include "SingleTon.h"
#include <mciapi.h>

class SoundManager :
	public SingleTon<SoundManager>
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	map<string, int> m_Sound;
	double time;
	double lasttime;
	bool activetime;
	int second;

public:
	void AddSound(string str, LPCWSTR route);
	void Playbgm(string str, bool loop);
	void RePlay(string str);
	void Pause(string str);
	void Close(string str);
	void PlayEffect(LPCWSTR route);
	void Update();
	void Release();
	int Getsecond() { return second; }

	SoundManager();
	virtual ~SoundManager();
};

#define SOUNDMANAGER SoundManager::GetSingleton()