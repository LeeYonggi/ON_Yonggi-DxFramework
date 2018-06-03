#pragma once
#include "SingleTon.h"
#include "WinMain.h"

const float MAX_SIZE_DIVISION = -SCREEN_HEIGHT;

struct Texture
{
	LPDIRECT3DTEXTURE9 _tex;
	D3DXIMAGE_INFO info;
};

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
	{
		_x = x;  _y = y;  _z = z;
	}
	float _x, _y, _z;
	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ;

struct ColorVertex
{
	D3DXVECTOR3 position;
	D3DCOLOR color;

	enum { FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE) };
	ColorVertex() { }
	ColorVertex(D3DXVECTOR3 pos, D3DCOLOR col) : position(pos), color(col) { }
};

struct NormalTexVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex;

	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	NormalTexVertex() { }
	NormalTexVertex( D3DXVECTOR3 pos, D3DXVECTOR3 _normal, D3DXVECTOR2 _tex) 
		: position(pos), normal(_normal), tex(_tex) { }
};

class RenderingManager :
	public SingleTon<RenderingManager>
{
private:
	IDirect3DVertexBuffer9 *vb;
	IDirect3DIndexBuffer9 *ib;
	D3DXVECTOR3 viewposition;
	D3DXVECTOR3 viewtargetPoint;
	D3DXVECTOR3 viewworldUp;
	vector<ColorVertex> vertex;
	vector<NormalTexVertex> _vertex;
	Texture *texture;
	D3DMATERIAL9 _mtl;
	map<string, Texture*> mTexture;
	float vangleY;

public:
	HRESULT Createbuffer();
	void Init();
	void DrawPrimitive();
	void DrawPrimitiveUp();
	void View();
	void SetViewAngle(float angle)
	{
		vangleY = angle;
	}
	void Release();

	//2D ImageManager
	void AddImage(string key, LPCSTR route);
	HRESULT DrawImage(string key, D3DXVECTOR3 pos, D3DXVECTOR3 angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		float alpha = 255.0f, float scale = 1.0f);

	RenderingManager();
	virtual ~RenderingManager();
};

#define RENDERINGMANAGER RenderingManager::GetSingleton()