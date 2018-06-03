#pragma once
#include "SingleTon.h"

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
	NormalTexVertex(D3DXVECTOR3 pos, D3DXVECTOR3 _normal, D3DXVECTOR2 _tex)
		: position(pos), normal(_normal), tex(_tex) { }
};

struct Color
{
	int r, g, b, alpha;

	Color() { }
	Color(int _r, int _g, int _b, int _alpha)
	{
		r = _r; g = _g; b = _b; alpha = _alpha;
	}
	~Color() { }
};

class Texture;
class DataManager :
	public SingleTon<DataManager>
{
private:
	map<string, Texture*> m_TextureData;
	map<string, vector<Texture*>*> m_animeData;
	vector<NormalTexVertex> _vertex;

public:
	Texture *AddTexture(string str, LPCWSTR route);
	Texture *GetTexture(string str);
	vector<Texture*>* AddanimeTexture(string str, LPCWSTR route, int low, int high);
	vector<Texture*>* GetanimeTexture(string str);
	vector<NormalTexVertex> GetVertexRect() { return _vertex; }
	DataManager();
	virtual ~DataManager();
};

#define DATAMANAGER DataManager::GetSingleton()