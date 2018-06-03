#include "stdafx.h"
#include "cTime.h"


void cTime::AddNowTime()
{
	nowTime = timeGetTime();
}

void cTime::AddLastTime()
{
	lastTime = timeGetTime();
}

cTime::cTime()
{
}


cTime::~cTime()
{
}
