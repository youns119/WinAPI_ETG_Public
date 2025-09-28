#pragma once

#include "UI.h"

class CFear : public CUI
{
public :
	CFear();
	virtual ~CFear();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

private :
	int m_iFear;

	float m_fDistance;
};