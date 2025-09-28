#pragma once

#include "Effect.h"

class CTableEffect : public CEffect
{
public :
	CTableEffect();
	virtual ~CTableEffect();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void CreateAnimation() override;
};