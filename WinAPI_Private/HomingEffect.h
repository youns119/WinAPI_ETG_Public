#pragma once

#include "Effect.h"

class CHomingEffect : public CEffect
{
public :
	CHomingEffect();
	virtual ~CHomingEffect();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void CreateAnimation() override;
};