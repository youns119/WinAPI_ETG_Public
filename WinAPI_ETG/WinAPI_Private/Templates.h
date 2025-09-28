#pragma once

template<typename T>
void Safe_Delete(T& _Temp)
{
	if (_Temp)
	{
		delete _Temp;
		_Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Vec(vector<T>& _Vec)
{
	for (size_t i = 0; i < _Vec.size(); i++)
	{
		if (_Vec[i])
		{
			delete _Vec[i];
			_Vec[i] = nullptr;
		}
	}

	_Vec.clear();
}

template <typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _Map)
{
	typename map<T1, T2>::iterator iter = _Map.begin();

	for (; iter != _Map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	_Map.clear();
}

template<typename T>
void Zero(T& _Temp)
{
	if (_Temp) ZeroMemory(&_Temp, sizeof(T));
}