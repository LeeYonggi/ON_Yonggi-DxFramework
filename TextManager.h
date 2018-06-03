#pragma once
#include "SingleTon.h"
class TextManager :
	public SingleTon<TextManager>
{
private:
	LPD3DXFONT m_lpFont01;

public:
	void Init();
	void Release();
	void Drawtext(LPCWSTR str, D3DXVECTOR2 pos, int type, Color color);

	TextManager();
	virtual ~TextManager();
};

#define TEXTMANAGER TextManager::GetSingleton()