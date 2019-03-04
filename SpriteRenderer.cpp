#include "stdafx.h"
#include "SpriteRenderer.h"


HRESULT SpriteRenderer::AddImage(string str, LPCWSTR route)
{
	texture = DATAMANAGER->AddTexture(str, route);

	transform = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	color = { 255, 255, 255, 255 };

	return S_OK;
}

HRESULT SpriteRenderer::AddanimeImage(string str, LPCWSTR route, int low, int high, float animedelay)
{
	animeTexture = DATAMANAGER->AddanimeTexture(str, route, low, high);

	transform = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } };
	color = { 255, 255, 255, 255 };
	this->animedelay = animedelay;

	return S_OK;
}

HRESULT SpriteRenderer::DrawImage(Texture *tex, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 angle, Color color)
{
	D3DXMATRIX matWorld, matS, matRZ, matRX, matRY, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);

	D3DXMatrixRotationX(&matRX, angle.x);
	D3DXMatrixRotationZ(&matRZ, angle.z);
	D3DXMatrixRotationY(&matRY, angle.y);

	D3DXMATRIX matR = matRZ * matRX * matRY;

	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matWorld = matS * matR * matT;

	lp_sprite->SetTransform(&matWorld);

	D3DXVECTOR3 center = { (FLOAT)tex->info.Width / 2, (FLOAT)tex->info.Height / 2, 0 };

	lp_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	lp_sprite->Draw(tex->_tex, nullptr, &center, nullptr, D3DCOLOR_RGBA(color.r, color.g, color.b, color.alpha));

	lp_sprite->End();
	return S_OK;
}

void SpriteRenderer::Render()
{
	if (anime == false)
	{
		DrawImage(texture, transform.position + GetObject_()->GetTransform().position,
			transform.scale + GetObject_()->GetTransform().scale,
			transform.rotation + GetObject_()->GetTransform().rotation, color);
	}
	else
	{
		auto iter = *animeTexture;
		DrawImage(iter[(INT)nowImage], transform.position + GetObject_()->GetTransform().position,
			transform.scale + GetObject_()->GetTransform().scale,
			transform.rotation + GetObject_()->GetTransform().rotation, color);

		if (frame <= timeGetTime())
		{
			frame = timeGetTime() + animedelay;
			nowImage += TIMEMANAGER->GetDeltaTime() * 50;
			cout << nowImage << endl;
			if (nowImage >= iter.size())
				nowImage = 0.0f;
		}
	}
}

SpriteRenderer::SpriteRenderer()
{
	anime = false;
	animedelay = 0.0f;
	frame = 0.0f;
	nowImage = 0;
}


SpriteRenderer::~SpriteRenderer()
{
}
