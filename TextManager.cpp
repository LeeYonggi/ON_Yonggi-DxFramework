#include "stdafx.h"
#include "TextManager.h"

void TextManager::Init()
{
	D3DXCreateFont(DEVICE, 50, 0, 10, 1, false, DEFAULT_CHARSET, 0, 0, 0, TEXT("Fixedys"), &m_lpFont01);
}

void TextManager::Release()
{
	SAFE_RELEASE(m_lpFont01);
}

void TextManager::Drawtext(LPCWSTR str, D3DXVECTOR2 pos, int type, Color color)
{
	RECT re = { 0 };

	D3DXMATRIXA16 matT;

	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);
	lp_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	lp_sprite->SetTransform(&matT);

	m_lpFont01->DrawText(lp_sprite, str, lstrlen(str), &re, DT_CENTER, D3DCOLOR_RGBA(color.r, color.g, color.b, color.alpha));

	lp_sprite->End();
}

TextManager::TextManager()
{
	Init();
}


TextManager::~TextManager()
{
	Release();
}
