#include "stdafx.h"
#include "Object.h"
#include "Component.h"


Object::Object()
{
}


Object::~Object()
{
	for (auto iter : components)
	{
		SAFE_DELETE(iter.second);
	}
	components.clear();
}
