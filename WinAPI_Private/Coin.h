#pragma once

#include "UI.h"

class CCoin : public CUI
{
public :
	CCoin();
	virtual ~CCoin();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void CoinUpdate();
	void CoinOffset();

private :
	int m_iCoin;

	int m_iOffset;

private :
	vector<int> m_vecCount;
};