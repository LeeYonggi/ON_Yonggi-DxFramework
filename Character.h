#pragma once
#include "Object.h"
class Character :
	public Object
{
private:
	TexVertexRenderer *m_Sprite;
public:
	void Init();
	void Update();
	void Render();
	void Release();

	Character();
	virtual ~Character();
};

