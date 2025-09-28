#pragma once

#include "UI.h"

class CTexture;

class CBullet : public CUI
{
public :
	CBullet();
	virtual ~CBullet();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	CTexture* ChooseTexture();

private:
	int m_iMaxCount;
	int m_iCurrCount;

	float m_fDistance;
};