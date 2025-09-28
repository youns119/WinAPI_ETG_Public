#pragma once

#include "UI.h"

class CGun;

class CReload : public CUI
{
public :
	CReload();
	virtual ~CReload();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void SetAnimation();

private :
	float m_fSpeed;

private :
	CGun* m_pCurrGun;
};