#pragma once

#include "Projectile.h"

class CGun;

class CProjectile_Revolver : public CProjectile
{
public :
	CProjectile_Revolver();
	CProjectile_Revolver(CGun& pGun);
	virtual ~CProjectile_Revolver();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void ChooseTexture() override;

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;
};