#pragma once

#include "Projectile.h"

class CGun;

class CProjectile_MachineGun : public CProjectile
{
public:
	CProjectile_MachineGun();
	CProjectile_MachineGun(CGun& pGun);
	virtual ~CProjectile_MachineGun();

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