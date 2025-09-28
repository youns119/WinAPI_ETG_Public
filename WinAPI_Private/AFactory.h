#pragma once

#include "Object.h"

template<typename T>
class CAFactory
{
public:
	CAFactory() {}
	virtual ~CAFactory() {}

public:
	static CObject* Create()
	{
		CObject* pObject = new T;
		pObject->Init();

		return pObject;
	}

	static CObject* Create(const float _fX, const float _fY)
	{
		CObject* pObject = new T;

		pObject->Init();
		pObject->SetPos(_fX, _fY);

		return pObject;
	}
};