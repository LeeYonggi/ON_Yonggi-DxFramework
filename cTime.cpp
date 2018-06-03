#include "stdafx.h"
#include "cTime.h"




void cTime::Drawfps()
{
	if (fpstime <= timeGetTime())
	{
		fpstime = timeGetTime() + 1000.0f;
		cout << frameCount << endl;
		frameCount = 0;
	}
}

cTime::cTime()
{
	fpstime = timeGetTime();
}

cTime::~cTime()
{
}
