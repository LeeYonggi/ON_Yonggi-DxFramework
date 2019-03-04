#include "stdafx.h"
#include "RenderingManager.h"


HRESULT RenderingManager::Createbuffer()
{
	d3dxdevice->CreateVertexBuffer(
		8 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0);

	d3dxdevice->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib,
		0);

	return S_OK;
}

void RenderingManager::Init()
{
	viewposition =
	{
		0.0f, 0.0f, MAX_SIZE_DIVISION
	};
	viewtargetPoint =
	{
		0.0f, 0.0f, 0.0f
	};
	viewworldUp =
	{
		0.0f, 1.0f, 0.0f
	};
	vertex.push_back(ColorVertex(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1, 1, 1, 1)));
	vertex.push_back(ColorVertex(D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXCOLOR(1, 1, 1, 1)));
	vertex.push_back(ColorVertex(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXCOLOR(1, 1, 1, 1)));

	VOID *vertices;	
	vb->Lock(0, sizeof(ColorVertex), (void**)&vertices, 0);
	memcpy(vertices, &vertex[0], vertex.size() * sizeof(ColorVertex));
	vb->Unlock();

	ZeroMemory(&_mtl, sizeof(_mtl));
	_mtl.Ambient = _mtl.Diffuse = _mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	_vertex.push_back(NormalTexVertex(D3DXVECTOR3(1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0)));
	_vertex.push_back(NormalTexVertex(D3DXVECTOR3(1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 1)));
	_vertex.push_back(NormalTexVertex(D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1)));
	_vertex.push_back(NormalTexVertex(D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1)));
	_vertex.push_back(NormalTexVertex(D3DXVECTOR3(-1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 0)));
	_vertex.push_back(NormalTexVertex(D3DXVECTOR3(1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0)));

	vangleY = 0;
	//*
#ifdef _DEBUG

	AllocConsole();                 // Allocate console window

	freopen("CONOUT$", "a", stderr); // Redirect stderr to console

	freopen("CONOUT$", "a", stdout); // Redirect stdout also

	freopen("CONIN$", "r", stdin);

	SetConsoleTitleA("Test v.1.0");

#endif // DEBUG
	//*/
}

void RenderingManager::DrawPrimitive()
{
	d3dxdevice->SetStreamSource(0, vb, 0, sizeof(ColorVertex));
	d3dxdevice->SetFVF(ColorVertex::FVF);
	d3dxdevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	//d3dxdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vertex.size() / 3, &vertex[0], sizeof(vertex));
}

void RenderingManager::DrawPrimitiveUp()
{
	D3DXMATRIX matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, 1, 1, 1);
	D3DXMatrixRotationZ(&matR, 0);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	matWorld = matS * matR * matT;
	d3dxdevice->SetTransform(D3DTS_WORLD, &matWorld);

	d3dxdevice->SetFVF(NormalTexVertex::FVF);
	d3dxdevice->SetTexture(0, texture->_tex);
	d3dxdevice->SetMaterial(&_mtl);
	d3dxdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		_vertex.size() / 3,
		&_vertex[0],
		sizeof(NormalTexVertex));
	d3dxdevice->SetTexture(0, nullptr);
}

void RenderingManager::View()
{
	
	
	//d3dxdevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//d3dxdevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//d3dxdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void RenderingManager::Release()
{
	vb->Release();
	ib->Release();
	for (auto iter : mTexture)
	{
		SAFE_RELEASE(iter.second->_tex);
		SAFE_DELETE(iter.second);
	}
	mTexture.clear();
#ifdef _DEBUG
	FreeConsole();
#endif

}

void RenderingManager::AddImage(string key, LPCWSTR route)
{
	auto iter = mTexture.find(key);
	if (iter == mTexture.end())
	{
		Texture *tex = new Texture;
		D3DXCreateTextureFromFileEx(d3dxdevice, route, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
			1, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &tex->info, nullptr, &tex->_tex);
		mTexture.insert(make_pair(key, tex));
	}
}

HRESULT RenderingManager::DrawImage(string key, D3DXVECTOR3 pos, D3DXVECTOR3 angle, float alpha, float scale)
{
	auto iter = mTexture.find(key);
	if (iter != mTexture.end())
	{
		D3DXMATRIX matWorld, matS, matRZ, matRX, matRY, matT;
		D3DXMatrixScaling(&matS, iter->second->info.Width * scale,
			iter->second->info.Height * scale, 1);
		D3DXMatrixRotationX(&matRX, D3DXToRadian(angle.x));
		D3DXMatrixRotationY(&matRY, D3DXToRadian(angle.y));
		D3DXMatrixRotationZ(&matRZ, D3DXToRadian(angle.z));
		D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
		matWorld = matS * matRX * matRY * matRZ * matT;

		//device
		d3dxdevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		d3dxdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		d3dxdevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
		d3dxdevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA); //INVSRCALPHA를 쓰면 멋진걸 볼 수 있음
		d3dxdevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3dxdevice->SetTransform(D3DTS_WORLD, &matWorld);
		d3dxdevice->SetFVF(NormalTexVertex::FVF);
		d3dxdevice->SetTexture(0, iter->second->_tex);
		d3dxdevice->SetMaterial(&_mtl);
		d3dxdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			_vertex.size() / 3,
			&_vertex[0],
			sizeof(NormalTexVertex));
		d3dxdevice->SetTexture(0, nullptr);
	}
	else
		return S_FALSE;

	return S_OK;
}

RenderingManager::RenderingManager()
{
}


RenderingManager::~RenderingManager()
{
}
