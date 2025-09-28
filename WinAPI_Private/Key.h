#pragma once

#include "UI.h"

class CKey : public CUI
{
public :
	CKey();
	virtual ~CKey();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void KeyUpdate();

private :
	int m_iKey;

private :
	vector<int> m_vecCount;
};