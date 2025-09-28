#pragma once

#include "Object.h"

#include "EffectType.h"

class CTexture;

class CEffect : public CObject
{
public :
	CEffect();
	virtual ~CEffect();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	EFFECT_TYPE GetEffectType() const { return m_eEffectType; }

	void SetEffectType(const EFFECT_TYPE _eEffectType) { m_eEffectType = _eEffectType; }

private :
	EFFECT_TYPE m_eEffectType;
};