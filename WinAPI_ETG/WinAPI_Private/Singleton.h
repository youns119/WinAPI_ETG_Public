#pragma once

template<typename T>
class Singleton
{
public :
	static T* Get()
	{
		if (!instance)
			instance = new T;

		return instance;
	}

	void Destroy()
	{
		delete instance;
		instance = nullptr;
	}

protected :
	Singleton() {};
	virtual ~Singleton() {};

private :
	static T* instance;
};

template<typename T>
T* Singleton<T>::instance = nullptr;