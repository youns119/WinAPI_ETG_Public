#pragma once

#include "Gun.h"

class CShotGun : public CGun
{
public :
	CShotGun();
	virtual ~CShotGun();

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

		if (m_iSoundCount == 3)
			m_iSoundCount = 0;
	}

public :
	virtual void PreRender() override;

private:
	static int m_iSoundCount;
};