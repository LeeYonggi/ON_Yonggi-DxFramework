#pragma once


class Component
{
private:
	Object * obj;
	bool active;

protected:
	string tag;

public:
	virtual void Init() { }
	virtual void Update()  { }
	virtual void Render()  { }
	virtual void Release()  { }

	void SetObj(Object *object) { obj = object; }
	void SetActive(bool _active) { active = _active; }
	Object *GetObject_() { return obj; }
	bool GetActive() { return active; }
	string GetTag() { return tag; }

	Component();
	virtual ~Component();
};

