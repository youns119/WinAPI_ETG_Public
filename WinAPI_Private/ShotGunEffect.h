#pragma once

#include "Effect.h"

#include "ProjectileType.h"

class CShotGunEffect : public CEffect
{
public :
	CShotGunEffect();
	virtual ~CShotGunEffect();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void CreateAnimation() override;
};