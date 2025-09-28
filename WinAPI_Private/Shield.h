#pragma once

#include "UI.h"

class CShield : public CUI
{
public :
	CShield();
	virtual ~CShield();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

private:
	int m_iCount;
};