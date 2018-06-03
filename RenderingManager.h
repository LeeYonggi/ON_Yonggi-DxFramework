#pragma once
#include "SingleTon.h"
#include "WinMain.h"


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
	void AddImage(string key, LPCWSTR route);
	HRESULT DrawImage(string key, D3DXVECTOR3 pos, D3DXVECTOR3 angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		float alpha = 255.0f, float scale = 1.0f);

	RenderingManager();
	virtual ~RenderingManager();
};

#define RENDERINGMANAGER RenderingManager::GetSingleton()