#pragma once

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

class SpriteRenderer :
	public Component
{
private:
	Texture *texture;
	Color color;
public:
	HRESULT AddImage(string str, LPCSTR route);
	HRESULT DrawImage(string str, D3DXVECTOR2 pos, float scale = 1.0f, float angle = 0.0f,
		Color color = Color(255, 255, 255, 255));
	void Render();
	void SetColor(Color _color) { color = _color; }

	SpriteRenderer();
	virtual ~SpriteRenderer();
};
