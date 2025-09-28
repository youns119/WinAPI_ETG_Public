#pragma once

#include "UI.h"

class CTexture;

class CGunBox : public CUI
{
public :
	CGunBox();
	virtual ~CGunBox();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

private :
	CTexture* m_pGunTexture;
};