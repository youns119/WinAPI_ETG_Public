#pragma once

#include "Enemy.h"

#include "PatternType.h"
#include "BossState.h"
#include "BossChair.h"

class CProjectile;

class CBulletKing : public CEnemy
{
public :
	CBulletKing();
	virtual ~CBulletKing();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	BOSS_STATE GetBossState() const { return m_eBossState; }
	CObject* GetChair() const { return m_pChair; }

	void SetBossState(const BOSS_STATE _eBossState) { m_eBossState = _eBossState; }
	void SetChair(CObject* _pChair) { m_pChair = _pChair; }

public :
	virtual void Attack() override;

public :
	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();
	void Pattern5();

public :
	void CreateEffect();

public :
	virtual void Motion() override;
	virtual void CreateAnimation() override;

public :
	void ShotSound();
	void AddSoundCount()
	{
		m_iSoundCount++;

		if (m_iSoundCount == 3)
			m_iSoundCount = 0;
	}

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	bool m_bShow;
	bool m_bSpin;
	int m_iCount;
	int m_iSoundCount;
	float m_fDelay;
	float m_fPatternDelay;
	float m_fDeathTime;

	PATTERN_TYPE m_ePatternType;
	BOSS_STATE m_eBossState;

private :
	CObject* m_pChair;

private :
	vector<CProjectile*> m_vProjectile;
};