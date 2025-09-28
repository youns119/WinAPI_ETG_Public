#pragma once

#include "UI.h"

class CTexture;

class CMinimap : public CUI
{
public :
	CMinimap();
	virtual ~CMinimap();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

private :
	CTexture* m_pBack;
	CTexture* m_pPlayer;
	CTexture* m_pTexture;
};