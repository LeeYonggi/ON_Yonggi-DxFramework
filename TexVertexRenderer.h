#pragma once
#include "Component.h"
class TexVertexRenderer :
	public Component
{
private:
	Texture *texture;
	vector<Texture*>* animeTexture;
	Color color;
	Transform transform;
	bool anime; //if(animetion)
	float animedelay; //animetion delay
	float frame;
	float nowImage;

public:
	HRESULT AddImage(string str, LPCWSTR route); //ImageSave
	HRESULT AddanimeImage(string str, LPCWSTR route, int low, int high, float animedelay); //animetion Image Save
	HRESULT DrawImage(Texture *tex, D3DXVECTOR3 pos, D3DXVECTOR3 scale = { 1.0f, 1.0f, 1.0f },
		D3DXVECTOR3 angle = { 0.0f, 0.0f, 0.0f },
		Color color = Color(255, 255, 255, 255)); //Draw
	void Render() override; //Render
	void SetColor(Color _color) { color = _color; }
	void SetAnimeConfirm(bool set) { anime = set; }
	void SetVertex(Texture *tex) { texture = tex; }
	bool GetAnimeConfirm() { return anime; }
	void SetTransform(Transform _transform) { transform = _transform; }
	float GetNowImage() { return nowImage; }

	TexVertexRenderer();
	virtual ~TexVertexRenderer();
};

