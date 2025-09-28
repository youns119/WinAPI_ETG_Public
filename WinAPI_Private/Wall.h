#pragma once

#include "Object.h"

class CWall : public CObject
{
public :
	CWall();
	virtual ~CWall();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;
};