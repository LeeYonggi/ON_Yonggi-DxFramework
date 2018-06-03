#include "stdafx.h"
#include "SpriteRenderer.h"


HRESULT SpriteRenderer::AddImage(string str, LPCSTR route)
{
	Texture *tex = new Texture;
	D3DXCreateTextureFromFileEx
	(
		DEVICE,
		route,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0, &tex->info, nullptr, &tex->_tex
	);

	return S_OK;
}

HRESULT SpriteRenderer::DrawImage(string str, D3DXVECTOR2 pos, float scale, float angle, Color color)
{

	D3DXMATRIX matWorld, matS, matR, matT;

	D3DXMatrixScaling(&matS, scale, scale, 1);
	D3DXMatrixRotationZ(&matR, angle);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matWorld = matS * matR * matT;

	lp_sprite->SetTransform(&matWorld);

	D3DXVECTOR3 center = { (FLOAT)texture->info.Width / 2, (FLOAT)texture->info.Height / 2, 0 };

	lp_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	lp_sprite->Draw(texture->_tex, nullptr, &center, nullptr, D3DCOLOR_RGBA(color.r, color.g, color.b, color.alpha));

	lp_sprite->End();
	return S_OK;
}

void SpriteRenderer::Render()
{

}

SpriteRenderer::SpriteRenderer()
{
	D3DXCreateSprite(DEVICE, &lp_sprite);
}


SpriteRenderer::~SpriteRenderer()
{
	SAFE_RELEASE(texture->_tex);
	SAFE_DELETE(texture);
}
