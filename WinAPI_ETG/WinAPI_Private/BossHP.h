#pragma once

#include "UI.h"

class CBossHP : public CUI
{
public :
	CBossHP();
	virtual ~CBossHP();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void BossHPUpdate();

private :
	float m_fMaxHP;
	float m_fCurrHP;

	float m_fRatio;
};