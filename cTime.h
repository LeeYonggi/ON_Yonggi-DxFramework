#pragma once
#include "SingleTon.h"

class cTime : public SingleTon<cTime>
{
private:
	float lastTime;
	float nowTime;
	float deltaTime;

public:
	void AddNowTime();
	void AddLastTime();
	float GetDeltaTime()
	{
		deltaTime = nowTime - lastTime;
		return deltaTime;
	}

	cTime();
	virtual ~cTime();
};

#define TIMEMANAGER cTime::GetSingleton()