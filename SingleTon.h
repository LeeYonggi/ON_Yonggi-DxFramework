#pragma once

template<typename T>
class SingleTon
{
protected:
	static T *p;

public:
	static T* GetSingleton()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void ReleaseSingleton()
	{
		if (p)
			delete p;
		p = nullptr;
	}

	SingleTon() { }
	virtual ~SingleTon() { }
};

template<typename T>
T * SingleTon<T>::p = nullptr;	