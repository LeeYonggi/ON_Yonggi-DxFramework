#pragma once
#include "SingleTon.h"

const double timeScale = 0.001f;
const double frame = 1.0f / 60.0f;

class cTime : public SingleTon<cTime>
{
private:
	double deltaTime;
	float fpstime;
	float frameCount;

public:
	void Drawfps();
	void SetDeltaTime(double set) { deltaTime = set; }
	void AddCount() { frameCount += 1.0f; }
	double GetDeltaTime() { return deltaTime; }

	cTime();
	virtual ~cTime();
};

#define TIMEMANAGER cTime::GetSingleton()