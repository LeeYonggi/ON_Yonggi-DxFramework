#pragma once
class BaseScene
{
public:
	virtual void Init()   PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release()PURE;

	BaseScene() { }
	virtual ~BaseScene() { }
};

