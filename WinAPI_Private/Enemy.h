#pragma once

#include "Character.h"

#include "EnemyType.h"

class CEnemy : public CCharacter
{
public :
	CEnemy();
	virtual ~CEnemy();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	float GetRange() const { return m_fRange; }
	float GetSpeed() const { return m_fSpeed; }
	ENEMY_TYPE GetEnemyType() const { return m_eEnemyType; }
	CObject* GetTarget() const { return m_pTarget; }

	void SetRange(const float _fRange) { m_fRange = _fRange; }
	void SetSpeed(const float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetEnemyType(const ENEMY_TYPE _eEnemyType) { m_eEnemyType = _eEnemyType; }
	void SetTarget(CObject* _pTarget) { m_pTarget = _pTarget; }

public :
	virtual void Attack();

public :
	bool HitTimeCheck(float _fTime);

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	bool m_bItemCreated;
	bool m_bDespawn;
	float m_fRange;
	float m_fSpeed;
	float m_fDespawnTime;
	float m_fHitTime;
	
	ULONGLONG m_iHitTick;

	ENEMY_TYPE m_eEnemyType;

private :
	CObject* m_pTarget;
};