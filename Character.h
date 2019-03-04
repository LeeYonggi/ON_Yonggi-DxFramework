#pragma once
#include "Object.h"
class Character :
	public Object
{
private:
	TexVertexRenderer *m_sprite;
public:
	void Init();
	void Update();
	void Render();
	void Release();

	Character();
	virtual ~Character();
};

