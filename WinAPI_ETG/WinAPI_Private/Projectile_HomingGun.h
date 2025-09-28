#pragma once

#include "Projectile.h"

class CGun;

class CProjectile_HomingGun : public CProjectile
{
public :
	CProjectile_HomingGun();
	CProjectile_HomingGun(CGun& pGun);
	virtual ~CProjectile_HomingGun();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void Detonate();

public :
	virtual void ChooseTexture() override;

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	bool m_bHoming;

	float m_fHomingTime;
	float m_fEffectTime;

	ULONGLONG m_iHomingTick;
	ULONGLONG m_iEffectTick;

private :
	Vec2 m_vTarget;
};