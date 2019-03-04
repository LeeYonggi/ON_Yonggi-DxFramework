#pragma once

struct Transform
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

	Transform(D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DXVECTOR3 _scale)
		:position(_position), rotation(_rotation), scale(_scale)
	{ }

	Transform() 
	{
		position = { 0, 0, 0};
		rotation = { 0, 0, 0 };
		scale = { 1.0f, 1.0f, 1.0f };
	}
	~Transform() { }
};
class Component;
class Object
{
protected:
	bool active;
	bool destroy;
	Transform transform;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

	bool GetActive() { return active; }
	void SetActive(bool _active) { active = _active; }
	bool GetDestroy() { return destroy; }
	void SetDestroy(bool _destroy) { destroy = _destroy; }
	Transform GetTransform() { return transform; }
	void SetTransform(Transform _transform) { transform = _transform; }
	

	Object();
	virtual ~Object();

private://component
	std::map<string, Component*> components;

public: //component
	template<class T>
	T *AddComponent()	//코스트가 높기 때문에 많이쓰면 느려질 수 있음.
	{
		auto iter = components.find(typeid(T).name());
		if (iter != components.end()) { return dynamic_cast<T*>(iter->second); }
		
		T *tp = new T;
		tp->SetObj(this);
		components.insert(make_pair(typeid(*tp).name(), tp));
	}
	template<class T>
	T *GetComponent()
	{
		auto iter = components.find(typeid(T).name());
		if (iter == components.end())  return nullptr; 
		return dynamic_cast<T*>(iter->second);
	}
	map<string, Component*> GetComponents() { return components; }
};

