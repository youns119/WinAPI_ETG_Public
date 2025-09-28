#pragma once

#include "Gun.h"

class CPierceGun : public CGun
{
public :
	CPierceGun();
	virtual ~CPierceGun();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void PreRender() override;
};