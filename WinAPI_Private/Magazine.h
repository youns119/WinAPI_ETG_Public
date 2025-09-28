#pragma once

#include "UI.h"

#include "MagType.h"

class CGun;

class CMagazine : public CUI
{
public :
	CMagazine();
	virtual ~CMagazine();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void MaxUpdate();
	void CurrMaxUpdate();

private :
	int m_iCurrMax;

	vector<int> m_vecMax;
	vector<int> m_vecCurrMax;

private :
	CGun* m_pCurrGun;

	MAG_TYPE m_eMagType;
};