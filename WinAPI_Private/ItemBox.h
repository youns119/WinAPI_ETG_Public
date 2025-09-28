#pragma once

#include "UI.h"

class CTexture;

class CItemBox : public CUI
{
public :
	CItemBox();
	virtual ~CItemBox();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

private :
	CTexture* m_pItemTexture;
};