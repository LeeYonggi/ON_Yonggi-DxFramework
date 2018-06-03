#pragma once

class Component;
class Object
{
private:
	bool active;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

	bool GetActive() { return active; }
	void SetActive(bool _active) { active = _active; }

	Object();
	virtual ~Object();

private://component
	std::map<string, Component*> components;
public: //component
	template<class T>
	void AddComponent()
	{
		Component *p = new T;
		auto iter = components.find(p->GetTag());
		if (iter == components.end()) { delete p; return }
		p->SetObj(this);
		components.insert(make_pair(p->GetTag(), p));
	}
	template<class T>
	Component* GetComponent()
	{
		Component p = T;
		auto iter = components.find(p.tag);
		if (iter == components.end()) return nullptr;
		return iter->second;
	}
	map<string, Component*> M_GetComponent() { return components; }
};

