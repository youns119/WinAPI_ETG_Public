#pragma once

class IObject
{
public :
	virtual ~IObject() {};

public :
	virtual void Init()				PURE;
	virtual void Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC _hDC)	PURE;
	virtual void Release()			PURE;
};