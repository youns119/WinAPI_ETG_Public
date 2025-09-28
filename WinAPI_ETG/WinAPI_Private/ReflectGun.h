#pragma once

#include "Gun.h"

class CReflectGun : public CGun
{
public :
	CReflectGun();
	virtual ~CReflectGun();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	static int GetSoundCount() { return m_iSoundCount; }

	static void AddSoundCount()
	{
		m_iSoundCount++;

		if (m_iSoundCount == 2)
			m_iSoundCount = 0;
	}

public :
	virtual void PreRender() override;

private :
	static int m_iSoundCount;
};