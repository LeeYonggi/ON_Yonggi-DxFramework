#pragma once
#include "Object.h"
class Character :
	public Object
{
public:
	void Init();
	void Update();
	void Render();
	void Release();

	Character();
	virtual ~Character();
};

