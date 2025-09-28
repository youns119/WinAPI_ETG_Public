#pragma once

#include "Gun.h"

class CHomingGun : public CGun
{
public :
	CHomingGun();
	virtual ~CHomingGun();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void PreRender() override;
};