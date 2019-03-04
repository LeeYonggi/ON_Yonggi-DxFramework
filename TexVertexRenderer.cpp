#include "stdafx.h"
#include "TexVertexRenderer.h"


HRESULT TexVertexRenderer::AddImage(string str, LPCWSTR route)
{
	texture = DATAMANAGER->AddTexture(str, route);

	transform = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } };
	color = { 255, 255, 255, 255 };

	return S_OK;
}

HRESULT TexVertexRenderer::AddanimeImage(string str, LPCWSTR route, int low, int high, float animedelay)
{
	animeTexture = DATAMANAGER->AddanimeTexture(str, route, low, high);

	transform = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } };
	color = { 255, 255, 255, 255 };
	this->animedelay = animedelay;

	return S_OK;
}

HRESULT TexVertexRenderer::DrawImage(Texture * tex, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 angle, Color color)
{
	D3DXMATRIX matWorld, matS, matRZ, matRX, matRY, matT;
	D3DXVECTOR3 objPos, objScale, objRotate;
	objPos = GetObject_()->GetTransform().position;
	objScale = GetObject_()->GetTransform().scale;
	objRotate = GetObject_()->GetTransform().rotation;

	D3DXMatrixScaling(&matS, tex->info.Width * (scale.x + objScale.x),
		tex->info.Height * (scale.y + objScale.y), scale.z + objScale.z);
	D3DXMatrixRotationX(&matRX, D3DXToRadian(angle.x + objRotate.x));
	D3DXMatrixRotationY(&matRY, D3DXToRadian(angle.y + objRotate.y));
	D3DXMatrixRotationZ(&matRZ, D3DXToRadian(angle.z + objRotate.z));
	D3DXMatrixTranslation(&matT, pos.x + objPos.x, pos.y + objPos.y, pos.z + objPos.z);
	matWorld = matS * matRX * matRY * matRZ * matT;

	//device
	d3dxdevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	d3dxdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3dxdevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
	d3dxdevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA); 
	d3dxdevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	d3dxdevice->SetTransform(D3DTS_WORLD, &matWorld);

	d3dxdevice->SetFVF(NormalTexVertex::FVF);
	d3dxdevice->SetTexture(0, tex->_tex);

	D3DMATERIAL9 _mtl;
	_mtl.Ambient = _mtl.Diffuse = _mtl.Specular = D3DXCOLOR(color.r, color.g, color.b, color.alpha);
	d3dxdevice->SetMaterial(&_mtl);

	d3dxdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		DATAMANAGER->GetVertexRect().size() / 3,
		&DATAMANAGER->GetVertexRect()[0],
		sizeof(NormalTexVertex));
	d3dxdevice->SetTexture(0, nullptr);
	return S_OK;
}

void TexVertexRenderer::Render()
{
	if (anime == false)
	{
		DrawImage(texture, transform.position, transform.scale,	transform.rotation, color);
	}
	else
	{
		auto iter = *animeTexture;
		DrawImage(iter[(INT)nowImage], transform.position, transform.scale, transform.rotation, color);

		if (frame <= timeGetTime())
		{
			frame = timeGetTime() + animedelay;
			nowImage += TIMEMANAGER->GetDeltaTime() * 50;
			if (nowImage >= iter.size())
				nowImage = 0.0f;
		}
	}
}

TexVertexRenderer::TexVertexRenderer()
{
	anime = false;
	animedelay = 0.0f;
	frame = 0.0f;
	nowImage = 0;
}


TexVertexRenderer::~TexVertexRenderer()
{
}
