#pragma once

#include "Projectile.h"

class CGun;

class CProjectile_ShotGun : public CProjectile
{
public:
	CProjectile_ShotGun();
	CProjectile_ShotGun(CGun& pGun);
	virtual ~CProjectile_ShotGun();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void ChooseTexture() override;

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;
};