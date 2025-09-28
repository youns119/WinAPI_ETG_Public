#pragma once

#include "Projectile.h"

class CGun;

class CProjectile_ReflectGun : public CProjectile
{
public :
	CProjectile_ReflectGun();
	CProjectile_ReflectGun(CGun& pGun);
	virtual ~CProjectile_ReflectGun();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void ChooseTexture() override;

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;
};