#pragma once

#include "Effect.h"

#include "ProjectileType.h"

class CRevolverEffect : public CEffect
{
public :
	CRevolverEffect();
	virtual ~CRevolverEffect();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void CreateAnimation() override;
};