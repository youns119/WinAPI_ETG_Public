#pragma once

#include "UI.h"

class CHP : public CUI
{
public :
	CHP();
	virtual ~CHP();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void HPUpdate();

private :
	int m_iHP;

	int m_iHPFull;
	int m_iHPHalf;
	int m_iHPEmpty;

	float m_fDistance;
};