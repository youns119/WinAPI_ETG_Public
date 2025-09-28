#pragma once

#include "Effect.h"

class CBlowEffect : public CEffect
{
public :
	CBlowEffect();
	virtual ~CBlowEffect();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void CreateAnimation() override;
};